/*
 * @file		qbl-chat-message-send.cpp
 * @brief		Class to send message to recipient (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <cstdint>
#include <string>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <vector>

#include "qbl-chat-message-send.h"
#include "qbl-json-chat-message.h"
#include "qbl-json-chat-uuid.h"
#include "qbl-json-chat-uuid-mac.h"
#include "qbl.h"
#include "qbl-chat-history-internal.h"
#include "../crypto/qbl-rsa-stream.h"
#include "qbl-aes-stream.h"
#include "qbl-keygen.h"
#include "qbl-base64.h"
#include "qbl-curl.h"

QblChatMessageSend::QblChatMessageSend(IQblChatSend * caller, QblJsonChat json,
        QblJsonMainConfigContact * contact):
    QblObject(QblObject::CHAT), caller(caller), json(json), contact(contact)
{
    return;
}

QblChatMessageSend::~QblChatMessageSend()
{
    return;
}

void QblChatMessageSend::addMessageToQueue()
{
    Qbl *qbl;

    qbl = Qbl::getInstance();
    qbl->addMessageToQueue(this);

    return;
}

bool QblChatMessageSend::sendMessage()
{
    bool result = true;
    int res;
    std::string response;
    QblJsonChatMessage
        buffer((*(QblJsonChatMessage *) & this->json));
    
    
    std::string myString = buffer.getJsonString();
    
    QblCurl curl(this->contact->getInbox().getServer(), this->contact->getInbox().getPort());
    std::vector<uint8_t> myVector(myString.begin(), myString.end());


    uint8_t *p = &myVector[0];
    
    res = curl.post(this->contact->getInbox().getUri().c_str(), "", p, myString.length());
    
    switch (res) {
    case 200:
        response = curl.getResponseString();
        curl.checkResponse();
        
        result = true;
        this->json.setSendState(true);
        this->caller->messageSend(true);
        QblJsonChat::messageType type;
        
        type = this->json.getType();

        if (type >= QblJsonChat::CHAT && type <= QblJsonChat::CHAT_FILE_NEW) {
            QblChatHistoryInternal *history;
            Qbl *qbl;
            qbl = Qbl::getInstance();
            history = (QblChatHistoryInternal *) qbl->getChatHistory();
            history->addMessage(this->contact->getAlias(), this->json);
        }
        break;
    case 304:
        break;
    case 404:
        break;
    case 400:
        break;
    default:
        break;        
    }   
    return result;
}

QblJsonChat & QblChatMessageSend::getJsonString()
{
    return (this->json);
}

std::string QblChatMessageSend::createMessage()
{
    std::string str;
    std::string message;
    BIO *bufio = NULL;
    RSA *rsa = NULL;
    QblBase64 base64;
    std::vector<char> keyiv, key, *encKEYIV, iv, messageVector;
    QblRsaStream rsaStream;
    QblAesStream aesStream;
    std::string * encMessage, encKeyIvStr;

    // first line
    str.append("POST /").append(this->contact->getInbox().getUri())
        .append(" HTTP/1.1\n");
    // second line
    str.append("Host: ").append(this->contact->getInbox().getServer())
        .append(":").append(std::to_string(this->contact->getInbox().getPort()))
        .append("\n");
    str.append("Content-Type: application/x-www-form-urlencoded").append("\n");

    // TODO define other chat messages types
    switch (this->json.getType()) {
    case QblJsonChat::CHAT:
        {
            QblJsonChatMessage
                buffer((*(QblJsonChatMessage *) & this->json));

            message = buffer.getJsonString();
            break;
        }
    case QblJsonChat::UPLOAD_LINK:
        break;
    case QblJsonChat::UPLOAD_NEW_VERSION:
        {
            QblJsonChatUuid
                buffer((*(QblJsonChatUuid *) & this->json));

            message = buffer.getJsonString();
            break;
        }
        break;
    case QblJsonChat::UPLOAD_NEW_VERSION_MAC:
        {
            QblJsonChatUuidMac
                buffer((*(QblJsonChatUuidMac *) & this->json));

            message = buffer.getJsonString();
            break;
        }
        break;
    default:
        std::string errmsg = "Unhandled chat message type";
        std::string errorNumber = std::to_string(this->json.getType());
        throw QblException {
        errmsg, errorNumber};
    }

    str.append("Content-Length: ");

    // and add encrypted message
    str.append(std::to_string(message.size())).append("\n\n");
    str.append(message);

    return (str);
}
