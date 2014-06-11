/*
 * @file        qbl-ffsync.cpp
 * @brief       Class to sync data with firefox sync server
 * @author      Andre Fricke <afr@michael-wessel.de>
 * @author      Malte Zobel <zobel@praemandatum.de>
 * @author     Marcus Amler <ma@michael-wessel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-ffsync.h"
#include "qbl.h"
#include "../../src/crypto/qbl-aes-stream.h"
#include "../../src/digest/qbl-sha1-digest.h"
#include "../../src/hmac/qbl-sha256-hmac.h"
#include "../qbl-pipe.h"
#include "utf8.h"
#include <algorithm>
#include <string>
#include "../config/qbl-json-object.h"

#include "../../src/config/qbl-json-main-config.h"
#include <ctime>
#include <json_object.h>
#include <json.h>

#include "../../src/crypto/qbl-keygen.h"
#include "qbl-json-ffsync-record.h"
#include "qbl-json-ffsync-payload.h"

//
//TODO: HMAC in updateSpecBSO()
//TODO: get timestamps in sync()
//TODO: get UUID in sync()

FFSync::FFSync(std::string email, std::string password, std::string serverUrl, int port)
{
    //TODO: check if email and or username is needed
    this->email = email;
    this->password = password;
    this->serverUrl = serverUrl;
    this->port = port;
    this->cryptoKey = qblKeyGenAes256();
    this->username = email;
    this->auth = this->email + ":" + this->password;
    
    Qbl *qbl = Qbl::getInstance();
    QblJsonMainConfigFFSyncUser *ffsyncUser = new QblJsonMainConfigFFSyncUser();
    
    //the key needs to be base32 encoded to be json confrom for the config parser
    QblFFSyncBase32 b32;
    std::string keyStringB32 = b32.encode_Base32(this->cryptoKey);

    ffsyncUser->setKey(keyStringB32);
    ffsyncUser->setMail(this->email);
    ffsyncUser->setPassword(this->password);
    ffsyncUser->setUrl(this->serverUrl);
    ffsyncUser->setPort(this->port);
    ffsyncUser->setInterval(15);
    ffsyncUser->setUsername(this->email);

    qbl->getConfig()->getFFSyncUser()->integrate(ffsyncUser);
    qbl->getConfig()->configIsChanged();

    //TODO return crypto Key for User
}

FFSync::FFSync(std::string email, std::string password, std::string serverUrl, int port, std::string cryptoKey)
{
    std::vector<char> cryptoVector(cryptoKey.begin(), cryptoKey.end());

    //TODO: check if email and or username is needed
    this->email = email;
    this->password = password;
    this->serverUrl = serverUrl;
    this->port = port;
    this->cryptoKey = cryptoVector;
    this->username = encodeUsername();
    this->auth = this->username + ":" + this->password;

    Qbl *qbl = Qbl::getInstance();
    QblJsonMainConfigFFSyncUser *ffsyncUser = new QblJsonMainConfigFFSyncUser();

    //the key needs to be base32 encoded to be json confrom for the config parser
    QblFFSyncBase32 b32;
    std::string keyStringB32 = b32.encode_Base32(this->cryptoKey);

    ffsyncUser->setKey(keyStringB32);
    ffsyncUser->setMail(encodeUsername());
    ffsyncUser->setPassword(this->password);
    ffsyncUser->setUrl(this->serverUrl);
    ffsyncUser->setPort(this->port);
    ffsyncUser->setInterval(15);
    ffsyncUser->setUsername(encodeUsername());
    ffsyncUser->setModified(0.0);

    qbl->getConfig()->getFFSyncUser()->integrate(ffsyncUser);
    qbl->getConfig()->configIsChanged();

    //TODO return crypto Key for User
}

FFSync::FFSync()
{
    Qbl *qbl = Qbl::getInstance();
    QblJsonMainConfigFFSyncUser ffsyncUser;
    this->serverUrl = qbl->getConfig()->getFFSyncUser()->getUrl();
    this->port = qbl->getConfig()->getFFSyncUser()->getPort();
    this->password = qbl->getConfig()->getFFSyncUser()->getPassword();
    this->email = qbl->getConfig()->getFFSyncUser()->getMail();
    this->username = qbl->getConfig()->getFFSyncUser()->getUsername();

    std::string cryptoKeyString = qbl->getConfig()->getFFSyncUser()->getKey();

    QblFFSyncBase32 b32;
    std::vector<char> cryptoKeyDebased = b32.decode_Base32(cryptoKeyString);
    this->cryptoKey = cryptoKeyDebased;
    this->auth = this->username + ":" + this->password;

    return;
}

FFSync::~FFSync()
{
	return;
}
//TODO: necessary
void FFSync::initNewServer(std::string collection)
{
    settingsBlock setting;
    for (int i = 0; i <= 9; i++)
    {
        setting = static_cast<settingsBlock>(i);
        updateSpecBso(collection, setting);
    }
}

bool FFSync::sync(){
    bool result = false;
    settingsBlock setting;
    std::string collection = "collection";
    std::string localBlock;
    std::string serverBlock;

    QblCurl curl(this->serverUrl, this->port);

    std::string getInfo;
    Qbl *qbl = Qbl::getInstance();
    double serverUpdated = getTimestamp();
    const double localUpdated = qbl->getConfig()->getFFSyncUser()->getModified();
    if (serverUpdated == localUpdated) {
        result = true;
    }
    else if(serverUpdated < localUpdated) {
        for (int i = 0; i <= 9; i++)
        {
            setting = static_cast<settingsBlock>(i);
            updateSpecBso(collection, setting);
        }
        result = true;
    }
    else if(serverUpdated > localUpdated) {
        for (int i = 0; i <= 9; i++)
        {
            setting = static_cast<settingsBlock>(i);
            serverBlock = getBso(collection, setting, curl);
            QblJsonFFSyncRecord serverBlockJsonRecordObject;
            serverBlockJsonRecordObject.parse(serverBlock);

            //get the payload of the logical server block
            std::string serverBlockPayload = serverBlockJsonRecordObject.getPayload();

            QblJsonFFSyncPayload serverBlockPayloadObject;
            serverBlockPayloadObject.parse(serverBlockPayload);

            //get ciphertext an iv from the logical server block
            std::string serverBlockCipher = serverBlockPayloadObject.getCiphertext();
            std::string serverBlockIV = serverBlockPayloadObject.getIv();

            //the iv and cipher needs to get decoded of base32
            QblFFSyncBase32 b32;
            std::vector<char> serverBlockIVDebased = b32.decode_Base32(serverBlockIV);
            std::vector<char> serverBlockCipherDebased = b32.decode_Base32(serverBlockCipher);

            //convert the cipher into a string to decrypt it afterwards
            std::string serverBlockCipherString(serverBlockCipherDebased.begin(), serverBlockCipherDebased.end());

            std::string serverBlockDecrypted = serverBlockCipherString;//decrypt(serverBlockCipherString, serverBlockIVDebased);
            if(serverBlockDecrypted.length() <= 0)
            {
                serverBlockDecrypted = "{}";
            }else{

            setConfig(serverBlockDecrypted, setting);
            }
            result = true;
        }
    }
    return result;
}

//function to make use of the crypto class
std::string FFSync::encrypt(std::string input, std::vector<char> iv)
{
    QblAesStream a;

    a.init(this->cryptoKey,
        std::vector<char>(iv.begin(), iv.end()), QBL_CRYPTO_STREAM_ENCRYPT);

    std::string *encrypted = a.create(input);

    return *encrypted;
}
//function to make use of the crypto class
std::string FFSync::decrypt(std::string input, std::vector<char> iv)
{
    QblAesStream a;

    a.init(this->cryptoKey,
        std::vector<char>(iv.begin(), iv.end()), QBL_CRYPTO_STREAM_DECRYPT);

    std::string *decrypted = a.create(input);

    return *decrypted;
}

std::string FFSync::hmacSha256(std::string input)
{
    QblSha256Hmac a;

    a.init(this->cryptoKey);

    std::string *encrypted = a.create(input);

    return *encrypted;
}

//checks if a user exists on the server
std::string FFSync::checkUser()
{
    QblCurl curl(this->serverUrl, this->port);

    std::string resource ="user/1.0/" + this->username;

    int responseCode = curl.get(resource.c_str(), "");

    std::string response = curl.getResponseString();

    return response;
}
//checks the storage URL behind the sync server
std::string FFSync::getNode()
{
    QblCurl curl(this->serverUrl, this->port);

    std::string resource = "user/1.0/" + this->username + "/node/weave";

    int responseCode = curl.get(resource.c_str(), this->auth.c_str());

    std::string response = curl.getResponseString();
    return response;
}

std::string FFSync::encodeUsername()
{
    QblFFSyncBase32 b32;
    std::string tmp = this->email;

    //username toUTF8 (needs to get changed to ASCII)
    std::string temp;
    utf8::replace_invalid(tmp.begin(), tmp.end(), back_inserter(temp));
    tmp = temp;

    //toSHA1
    QblSha1Digest a;
    a.init();
    std::string* foo = a.create(tmp);
    std::string dereffoo = *foo;

    //toByteArray
    std::vector<char> data(dereffoo.begin(), dereffoo.end());

    //toBase32
    std::string result = b32.encode_Base32(data);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);

    return result;
}
//creates a user on the server
std::string FFSync::createUser(std::string email)
{
    QblCurl curl(this->serverUrl, this->port);

    std::string auth = this->username + ":" + this->password;
    std::string resource = "user/1.0/" + this->username;

    std::string data = "{\"password\": \"" + this->password + "\", \"email\": \"" + email + "\"}";

    const uint8_t* jsonData = reinterpret_cast<const uint8_t*>(data.c_str());

    int responseCode = curl.putJson(resource.c_str(), "", jsonData, data.length());

    std::string response = curl.getResponseString();

    Qbl *qbl = Qbl::getInstance();
    qbl->getConfig()->getFFSyncUser()->setMail(email);
    qbl->getConfig()->getFFSyncUser()->setPassword(this->password);
    qbl->getConfig()->getFFSyncUser()->setUsername(this->username);
    qbl->getConfig()->getFFSyncUser()->setUrl(this->serverUrl);

    qbl->getConfig()->configIsChanged();
    return response;

}
//get all record ids of a specific collection
std::string FFSync::getBsoList(std::string path)
{
    QblCurl curl(this->serverUrl, this->port);
    std::string resource = "1.1/" + this->username +"/storage/" + path;

    int responseCode = curl.get(resource.c_str(), this->auth.c_str());

    std::string response = curl.getResponseString();

    return response;
}
//get the content of a specific record
std::string FFSync::getBso(std::string collection, settingsBlock setting, QblCurl curl)
{
    std::string recordId;

    switch(setting){
        case ACCOUNTS:
            recordId = "accounts";
            break;
        case BLOCK_SERVERS:
            recordId = "blockServers";
            break;
        case CONTACTS:
            recordId = "contacts";
            break;
        case DROP_SERVERS:
            recordId = "dropServers";
            break;
        case FFSYNC_USER:
            recordId = "ffsyncUser";
            break;
        case GROUPS:
            recordId = "groups";
            break;
        case IDENTITIES:
            recordId = "identities";
            break;
        case PREFERENCES:
            recordId = "preferences";
            break;
        case SHARES:
            recordId = "shares";
            break;
        case UPLOADS:
            recordId = "uploads";
            break;
        default:
            return "Cannot find record ID";
    }

    
    std::string resource = "1.1/" + this->username + "/storage/" + collection + "/" + recordId;

    int responseCode = curl.get(resource.c_str(), this->auth.c_str());

    uint8_t *data = curl.getResponse();
    std::string response(reinterpret_cast<char *>(data), curl.getResponseSize());

    if(responseCode == 404){
        response = "404";
    }

    return response;

}
//changes the password on the server
std::string FFSync::changePassword(std::string newPassword)
{
   QblCurl curl(this->serverUrl, this->port);
    std::string resource ="user/1.0/" + this->username + "/password";

    const uint8_t* data = reinterpret_cast<const uint8_t*>(newPassword.c_str());
    int responseCode = curl.post(resource.c_str(), this->auth.c_str(), data, newPassword.length());

    std::string response = curl.getResponseString();

    return response;

    //TODO check if response was ok then write newPW to config file
}


std::string FFSync::getCollectionCounts()
{
    QblCurl curl(this->serverUrl, this->port);
    std::string resource = "1.1/" + this->username + "/info/collection_counts";

    int responseCode = curl.get(resource.c_str(), this->auth.c_str());

    std::string response = curl.getResponseString();

    return response;
}

double FFSync::getTimestamp()
{
    QblCurl curl(this->serverUrl, this->port);
    std::string resource = "1.1/" + this->username + "/info/collections";

    int responseCode = curl.get(resource.c_str(), this->auth.c_str());

    std::string response = curl.getResponseString();

    double timestamp;
    enum json_type type;
    json_object * json;
    json = json_tokener_parse(response.c_str());

    json_object_object_foreach(json, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_double:
                timestamp = json_object_get_double(val);
                //TODO error handling when there are multiple collections
        }
    }

    return timestamp;
}

//deletes a specific collection
std::string FFSync::deleteSpecificCollection(std::string collection)
{
    std::string resource = "1.1/" + this->username + "/storage/" + collection;
    return deleteRequest(resource, "X-Confirm-Delete: 1");
}
//delets specific record
std::string FFSync::deleteSpecificBSO(std::string collection, std::string bsoIds)
{
    std::string resource = "1.1/" + this->username + "/storage/" + collection + "/" + bsoIds;
    return deleteRequest(resource, "X-Confirm-Delete: 1");
}
//delets a user on the server
std::string FFSync::deleteUser()
{
    std::string resource = "user/1.0/" + this->username;
    return deleteRequest(resource, "X-Confirm-Delete: 1");
}
//delets all collections with their records of 1 user
std::string FFSync::deleteUserstorage()
{
    std::string resource = "1.1/" + this->username + "/storage";
    return deleteRequest(resource, "X-Confirm-Delete: 1");
}
//the ist just the delete request to avoid renundant code in the delete functions abobe
std::string FFSync::deleteRequest(std::string url, std::string contentType) {

    QblCurl curl(this->serverUrl, 5000);

    int responseCode = curl.del(url.c_str(), this->auth.c_str(), contentType);

    std::string response = curl.getResponseString();

    return response;
}
//TODO: settings to recordID ? updates a specific record
std::string FFSync::updateSpecBso(std::string collection, settingsBlock setting)
{
    std::string syncData = getConfig(setting);
    std::string recordId;

    switch(setting){
        case ACCOUNTS:
            recordId = "accounts";
            break;
        case BLOCK_SERVERS:
            recordId = "blockServers";
            break;
        case CONTACTS:
            recordId = "contacts";
            break;
        case DROP_SERVERS:
            recordId = "dropServers";
            break;
        case FFSYNC_USER:
            recordId = "ffsyncUser";
            break;
        case GROUPS:
            recordId = "groups";
            break;
        case IDENTITIES:
            recordId = "identities";
            break;
        case PREFERENCES:
            recordId = "preferences";
            break;
        case SHARES:
            recordId = "shares";
            break;
        case UPLOADS:
            recordId = "uploads";
            break;
        default:
            return "Cannot find record ID";
    }

    QblFFSyncBase32 b32;
    QblCurl curl(this->serverUrl, this->port);
    std::string resource = "1.1/" + username + "/storage/" + collection + "/" + recordId;
    time_t timestamp = time(0);

    //Crypto begin
    std::vector<char> iv = qblKeyGenAes256IV();
    std::string encryptedData = syncData;//encrypt(syncData, iv);
    //Crypto end

    std::vector<char> data(encryptedData.begin(), encryptedData.end());
    std::string ciphertext = b32.encode_Base32(data);
    std::string sendIv = b32.encode_Base32(iv);

    //TODO get HMAC

    QblJsonFFSyncPayload payloadJson;
    QblJsonFFSyncRecord recordJson;
    std::string payload = payloadJson.createPayload(ciphertext, sendIv, "hmac");
    std::string record = recordJson.createRecord(payload, std::to_string(timestamp), recordId);

    const uint8_t* jsonData = reinterpret_cast<const uint8_t*>(record.c_str());

    int responseCode = curl.putJson(resource.c_str(), this->auth.c_str(), jsonData, record.length());
    std::string response = curl.getResponseString();

    //write last updated time to local config
    Qbl *qbl = Qbl::getInstance();

    qbl->getConfig()->getFFSyncUser()->setModified(atof(response.c_str()));
    qbl->getConfig()->configIsChanged();

    return response;
}

//TODO check if method is necessary
std::string FFSync::jsonToString(){
    QblJsonMainConfig *configFile = new QblJsonMainConfig();
    const std::string data = configFile->getJsonString();
    std::string config = escapeJsonString(data);
    return config;
}

std::string FFSync::escapeJsonString(const std::string& input) {
    std::ostringstream ss;
    for (auto iter = input.begin(); iter != input.cend(); iter++) {
        switch (*iter) {
            case '"': ss << "\\\""; break;
            default: ss << *iter; break;
        }
    }
    return ss.str();
}
// gets a logical block of the local config depending on the setting
std::string FFSync::getConfig(settingsBlock setting) 
{
    Qbl *qbl = Qbl::getInstance();
    std::string config;
       
    switch(setting){
        case ACCOUNTS:
            config += "{";
            config += qbl->getConfig()->getAccounts()->getJsonString();
            config += "}";
            break;
        case BLOCK_SERVERS:
            config += "{";
            config += qbl->getConfig()->getBlockServers()->getJsonString();
            config += "}";
            break;
        case CONTACTS:
            config += "{";
            config += qbl->getConfig()->getContacts()->getJsonString();
            config += "}";
            break;
        case DROP_SERVERS:
            config += "{";
            config += qbl->getConfig()->getDropServers()->getJsonString();
            config += "}";
            break;
        case FFSYNC_USER:
            config += "{";
            config += qbl->getConfig()->getFFSyncUser()->getJsonString();
            config += "}";
            break;
        case GROUPS:
            config += "{";
            config += qbl->getConfig()->getGroups()->getJsonString();
            config += "}";
            break;
        case IDENTITIES:
            config += "{";
            config += qbl->getConfig()->getIdentities()->getJsonString();
            config += "}";
            break;
        case PREFERENCES:
            config += "{";
            config += qbl->getConfig()->getPreferences()->getJsonString();
            config += "}";
            break;
        case SHARES:
            config += "{";
            config += qbl->getConfig()->getShares()->getJsonString();
            config += "}";
            break;
        case UPLOADS:
            config += "{";
            config += qbl->getConfig()->getUploads()->getJsonString();
            config += "}";
            break;
        default:
            return "Cannot find record ID";
    }
    return config;
}
// gets the timestamp of a logical block of the local config depending on the setting
std::string FFSync::getConfigTimestamp(settingsBlock setting)
{
    Qbl *qbl = Qbl::getInstance();
    std::string config;

    switch(setting){
        case ACCOUNTS:
            config = qbl->getConfig()->getAccounts()->getUpdated();
            break;
        case BLOCK_SERVERS:
            config = qbl->getConfig()->getBlockServers()->getUpdated();
            break;
        case CONTACTS:
            config = qbl->getConfig()->getContacts()->getUpdated();
            break;
        case DROP_SERVERS:
            config = qbl->getConfig()->getDropServers()->getUpdated();
            break;
        case FFSYNC_USER:
            config = qbl->getConfig()->getFFSyncUser()->getUpdated();
            break;
        case GROUPS:
            config = qbl->getConfig()->getGroups()->getUpdated();
            break;
        case IDENTITIES:
            config = qbl->getConfig()->getIdentities()->getUpdated();
            break;
        case PREFERENCES:
            config = qbl->getConfig()->getPreferences()->getUpdated();
            break;
        case SHARES:
            config = qbl->getConfig()->getShares()->getUpdated();
            break;
        case UPLOADS:
            config = qbl->getConfig()->getUploads()->getUpdated();
            break;
        default:
            return "Cannot find record ID";
    }

    return config;
}
//set a logical block of the local config depending of the setting. needed if a server block is newer
void FFSync::setConfig(std::string configData, settingsBlock setting) 
{
    //TODO: Check if string is Empty
    Qbl *qbl = Qbl::getInstance();
    
    switch(setting){
        case ACCOUNTS:
        {
            QblJsonMainConfigAccountArray accountImport;
            accountImport.parse(configData);
            qbl->getConfig()->getAccounts()->integrate(&accountImport);            
            break;
        }
        case BLOCK_SERVERS:
        {
            QblJsonMainConfigBlockServerArray blockServerImport;
            blockServerImport.parse(configData);
            qbl->getConfig()->getBlockServers()->integrate(&blockServerImport);
            break;
        }
        case CONTACTS:
        {
            QblJsonMainConfigContactArray contactImport;
            contactImport.parse(configData);
            qbl->getConfig()->getContacts()->integrate(&contactImport);
            break;
        }
        case DROP_SERVERS:
        {
            QblJsonMainConfigDropServerArray dropServerImport;
            dropServerImport.parse(configData);
            qbl->getConfig()->getAccounts()->integrate(&dropServerImport);
            break;
        }
        case FFSYNC_USER:
        {
            QblJsonMainConfigFFSyncUser ffsyncImport;
            ffsyncImport.parse(configData);
            qbl->getConfig()->getFFSyncUser()->integrate(&ffsyncImport);
            break;
        }
        case GROUPS:
        {
            QblJsonMainConfigGroupArray groupsImport;
            groupsImport.parse(configData);
            qbl->getConfig()->getGroups()->integrate(&groupsImport);
            break;
        }
        case IDENTITIES:
        {
            QblJsonMainConfigIdentityArray identitiesImport;
            identitiesImport.parse(configData);
            qbl->getConfig()->getIdentities()->integrate(&identitiesImport);
            break;
        }
        case PREFERENCES:
        {
            QblJsonMainConfigPreferences preferencesImport;
            preferencesImport.parse(configData);
            qbl->getConfig()->getPreferences()->integrate(&preferencesImport);
            break;
        }
        case SHARES:
        {
            QblJsonMainConfigShareArray shareImport;
            shareImport.parse(configData);
            qbl->getConfig()->getShares()->integrate(&shareImport);
            break;
        }
        case UPLOADS:
        {
            QblJsonMainConfigUploadArray uploadImport;
            uploadImport.parse(configData);
            qbl->getConfig()->getUploads()->integrate(&uploadImport);
            break;
        }
        default:
        {
            //TODO 
        }
    }
    qbl->getConfig()->configIsChangedBySync(getTimestamp());
}
