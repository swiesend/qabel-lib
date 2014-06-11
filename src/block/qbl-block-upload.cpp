/*
 * @file		qbl-block-upload.cpp
 * @brief		Class to upload files (Implementation)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl.h"
#include "qbl-block-upload.h"
#include "qbl-zlib.h"
#include "qbl-curl.h"
#include "qbl-json-main-config-contact-array.h"
#include "qbl-json-chat-uuid.h"
#include "qbl-json-chat-uuid-mac.h"
#include "qbl-chat-message-send.h"

#include <fstream>
using namespace std;

QblBlockUpload::QblBlockUpload(QblJsonMainConfigShare *share) :
        IQblChatSend(), share(share) 
{
    Qbl *qbl;
    qbl = Qbl::getInstance();

    this->upload = qbl->getConfig()->getUploads()->getItem(
            this->share->getUploadId());
    this->server = qbl->getConfig()->getBlockServers()->getItem(
            this->upload->getBlockServerId());

    return;
}

QblBlockUpload::~QblBlockUpload()
{

    return;
}

void QblBlockUpload::pack()
{
    std::string output, uri, auth;
    std::vector<char> buffer;
    QblZlib *zlib;
    int file, retval;
    QblCurl *curl;
    std::list<int> *contacts;
    std::list<int>::iterator iterator;
    QblJsonMainConfigContactList realContacts;
    QblJsonMainConfigContactList::iterator contactIt;
    QblJsonMainConfigIdentityList identities;
    QblJsonMainConfigIdentityList::iterator identIt;
    Qbl *qbl;
    std::map<int64_t, QblJsonMainConfigIdentity *> map;
    std::map<int64_t, QblJsonMainConfigIdentity *>::iterator mapIt;

    this->build(this->share->getBasedir());

    this->writeInto(this->share->getKey(), &buffer);

    // zlib
    zlib = new QblZlib();
    buffer = zlib->compress(buffer);

    // TODO encrypt buffer

    // TODO delete it -> only for testing
    std::ofstream out;
    out.open("test.gz", std::ios_base::binary);
    if (out) {
        out.write(&buffer[0], buffer.size());
        out.close();
    }

    // TODO copy to storage
    uri = this->server->getPath();
    uri.append("/").append(this->upload->getPublic()).append("/");
    uri.append(std::to_string(this->share->getUuid()));
    auth = std::string("foo").append(":").append(this->upload->getToken());
    curl = new QblCurl(this->server->getServer(), this->server->getPort());
    retval = curl->postFile(uri.data(), auth.data(),
            (const uint8_t *) std::string(buffer.begin(), buffer.end()).data(),
            buffer.size());

    if (retval != 200) {
        return;
    }

    contacts = this->share->getContacts();
    qbl = Qbl::getInstance();
    realContacts = qbl->getConfig()->getContacts()->getList();
    identities = qbl->getConfig()->getIdentities()->getList();

    // TODO message to all which share this archive
    for (iterator = contacts->begin(); iterator != contacts->end();
            iterator++) {
        bool foundOne = false;
        for (contactIt = realContacts.begin(); contactIt != realContacts.end();
                contactIt++) {
            if ((*contactIt)->getUuid() == *iterator) {
                foundOne = true;
                break;
            }
        }
        if (foundOne == false) {
            std::string errmsg;
            errmsg = "Cannot find contact with id ";
            errmsg.append(std::to_string(*iterator));
            throw QblException { errmsg };
        }

        for (identIt = identities.begin(); identIt != identities.end();
                identIt++) {
            foundOne = false;

            if (!(*identIt)->getPublicKey().compare((*contactIt)->getMyId())) {
                QblChatMessageSend *message;
                foundOne = true;

                QblJsonChatUuid chat((*identIt)->getAlias(),
                        this->share->getUuid(),
                        QblJsonChat::UPLOAD_NEW_VERSION);
                message = new QblChatMessageSend(this, chat, *contactIt);
                message->addMessageToQueue();

                map.insert(
                        std::pair<int64_t, QblJsonMainConfigIdentity *>(
                                (*identIt)->getUuid(), *identIt));
                break;
            }

            if (foundOne == false) {
                std::string errmsg;
                errmsg = "Cannot find identity with id ";
                errmsg.append(std::to_string(*iterator));
                throw QblException { errmsg };
            }
        }
    }

    for (mapIt = map.begin(); mapIt != map.end(); mapIt++) {
        QblChatMessageSend *message;
        QblJsonMainConfigContact *contact;

        contact = new QblJsonMainConfigContact();
        contact->setAlias(mapIt->second->getAlias());
        contact->setInbox(mapIt->second->getInboxString());
        contact->setPublicKey(mapIt->second->getPublicKey());

        QblJsonChatUuidMac chat((*identIt)->getAlias(), this->share->getUuid(),
                QblJsonChat::UPLOAD_NEW_VERSION_MAC);
        message = new QblChatMessageSend(this, chat, contact);
        message->addMessageToQueue();
    }

    return;
}

void QblBlockUpload::pack(std::string sourcePath, std::string key,
        std::string url, std::string outputPath)
{
    std::string output;
    std::vector<char> buffer;
    QblZlib *zlib;
    int file;

    this->build(sourcePath);

    this->writeInto(key, &buffer);

    // zlib
    zlib = new QblZlib();
    buffer = zlib->compress(buffer);

    // TODO encrypt buffer

    // TODO delete it -> only for testing
    std::ofstream out;
    out.open("test.gz", std::ios_base::binary);
    if (out) {
        out.write(&buffer[0], buffer.size());
        out.close();
    }

    // TODO copy to storage

    return;
}

void QblBlockUpload::messageSend(bool done)
{
    return;
}
