/*
 * @file        qbl-ffsync.cpp
 * @brief       Class to sync data with firefox sync server (Header File)
 * @author      Andre Fricke <afr@michael-wessel.de>
 * @author      Malte Zobel <zobel@praemandatum.de>
 * @author     Marcus Amler <ma@michael-wessel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef FFSYNC_H
#define FFSYNC_H

#include <string>
#include "../net/qbl-curl.h"
#include <iostream>
#include "../../tests/result-listener.h"
#include "../config/qbl-json-object.h"


#include "qbl-ffsync-base32.h"

class FFSync : public QblJsonObject
{
public:
    enum settingsBlock {
        ACCOUNTS = 0,
        BLOCK_SERVERS = 1,
        CONTACTS = 2,
        DROP_SERVERS = 3,
        FFSYNC_USER = 4,
        GROUPS = 5,
        IDENTITIES = 6,
        PREFERENCES = 7,
        SHARES = 8,
        UPLOADS = 9,
    };    
    
    /**
     * Constructor for new user
     * @param username 
     * @param password
     * @param url
     * @param port
     * @return crypto Key
     */
    FFSync(std::string username, std::string password, std::string url, int port, std::string cryptoKey);
    FFSync(std::string username, std::string password, std::string url, int port);
    /**
     * Constructor for existing user
     */
    FFSync();
    /**
     * Destructor
     */
    ~FFSync();
    
    bool sync();

    void initNewServer(std::string collection);
    




    /**
     * Check if the username is available
     * @return 0 if available, 1 if not
     */
    std::string checkUser();
     /**
     * Encodes strings with aes265cbc
     * @return string
     */
    std::string encrypt(std::string input, std::vector<char> iv);
    /**
     * Encrypts a string with AES256cbc
     * @return Encrypted string
     */
    std::string decrypt(std::string input, std::vector<char> iv);
    /**
     * Decrypts a string with AES256cbc
     * @return Decrypted string
     */

    std::string hmacSha256(std::string input);

    //std::string getBso(std::string collection, settingsBlock setting);
    std::string getBso(std::string collection, settingsBlock setting, QblCurl curl);
    /**
     * Get the encrypted config File from the Server and decrypts it
     * @return ?
     */
    std::string encodeUsername();
    /**
     * Get the server uri of the server where the data is stored
     * @return server uri
     */
    std::string getNode();
    /**
     * Create user account on ffsync server
     * @param email
     * @return encoded username on success
     */
    std::string createUser(std::string email);
    /**
     * 
     * @param path
     * @return 
     */
    std::string getBsoList(std::string path);
    /**
     * Change the user password
     * @param newPassword
     * @return "success" when the password is changed
     */
    std::string changePassword(std::string newPassword);
    /**
     * Get a json object with the collections on the server and the amount of records they contain
     * @return json object
     */
    std::string getCollectionCounts();
    /**
     * Send delete request to url
     * @param url
     * @return body of http response
     */
    std::string deleteRequest(std::string url, std::string contentType);
    //std::string deleteAllCollections();
    /**
     * Deletes an entire collection
     * @param collection
     * @return 
     */
    std::string deleteSpecificCollection(std::string collection);
    /**
     * Deletes an record with the id ID from the collection collection
     * @param collection
     * @param ID
     * @return 
     */
    std::string deleteSpecificBSO(std::string collection, std::string ID);
    /**
     * Deletes the current ffsync user from server
     * @return 
     */
    std::string deleteUser();
    /**
     * Deletes the entire data on the server
     * @return 
     */
    std::vector<char> getKey();
    /**
     * function to get the key from dunno yet
     * @return
     */
    std::vector<char> getIV();
    /**
     * function to get the IV from the server
     * @return
     */
    /**
     * @brief getTimestamps
     * @return json string with last modified timestamp of collection
     */
    double getTimestamp();

    std::string deleteUserstorage();
    //QJsonObject readJson(std::string collection, std::string record, std::string ciphertext, std::string IV, std::string hmac);

    std::string updateSpecBso(std::string collection, settingsBlock setting);
    
    std::string jsonToString();
    std::string escapeJsonString(const std::string& input);
    std::string getConfig(settingsBlock setting);
    std::string getConfigTimestamp(settingsBlock setting);
    
    
    void setConfig(std::string configData, settingsBlock setting);   

private:
    std::string serverUrl;
    int port;
    std::string password;
    std::string response;
    std::string node;
    std::string email;
    std::string username;
    std::string auth;
    std::vector<char> cryptoKey;
};

#endif // FFSYNC_H
