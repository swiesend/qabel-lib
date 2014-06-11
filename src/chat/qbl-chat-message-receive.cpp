/*
 * @file		qbl-chat-message-receive.cpp
 * @brief		Class to receive message to recipient (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-chat-message-receive.h"

#include <stddef.h>
#include <cstdint>
#include <cstdio>
#include <string>

#include "qbl.h"
#include "qbl-chat-history-internal.h"
#include "qbl-curl.h"
#include "../crypto/qbl-rsa-stream.h"

QblChatMessageReceive::QblChatMessageReceive(QblJsonMainConfigIdentity *identity) :
		QblObject(QblObject::CHAT), identity(identity)
{

	return;
}

QblChatMessageReceive::~QblChatMessageReceive()
{

	return;
}

bool QblChatMessageReceive::sendMessage()
{
    bool result = true;
    int res;
    QblCurl curl(this->identity->getInbox().getServer(), this->identity->getInbox().getPort());

    if(this->identity->getLastUpdate().empty()) {
        res = curl.get(this->identity->getInbox().getUri().c_str(), "");
    }
    else {
        res =
            curl.getModifiedSince(this->identity->getInbox().getUri().c_str(), 
                    this->identity->getLastUpdate());
    }
    
    switch (res) {
    case 200:      
        this->checkReceivedMessage(curl.getResponseString());
        curl.checkResponse();
        this->identity->setLastUpdate(curl.getDate());
        Qbl *qbl;
        qbl = Qbl::getInstance();
        qbl->getConfig()->configIsChanged();
        
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

std::string QblChatMessageReceive::createMessage()
{
	std::string str;
	std::string json;

	// first line
	str.append("GET /").append(this->identity->getInbox().getUri())
        .append(" HTTP/1.1\n");
	// second line
	str.append("Host: ").append(this->identity->getInbox().getServer())
        .append(":")
        .append(std::to_string(this->identity->getInbox().getPort()))
        .append("\n");
	// third line -> accept
	str.append("Accept: */*\n");
	// fourth line -> last modification
	str.append("if-modified-since: ").append(this->identity->getLastUpdate())
        .append("\n");
	str.append("\n");

	return (str);
}



int QblChatMessageReceive::checkReceivedMessage(std::string msg)
{
	std::string buffer;
	size_t _length;
	bool foundMsg = false;
	int count = 0;
	QblJsonChat *chat = NULL;

	while (1) {
		_length = msg.find("\n");
		if (_length == string::npos) {
			break;
		}
		buffer = msg.substr(0, _length);
		if (buffer.at(_length - 1) == '\r') {
			buffer = msg.substr(0, _length - 1);
		}
		msg = msg.substr(_length + 1);
		if (foundMsg == false) {
			if (buffer.size() < 2) {
				continue;
			} else if (buffer.at(0) == '-' && buffer.at(1) == '-') {
				foundMsg = true;
				continue;
			}
			continue;
		}
		switch (count) {
		case 0:						// Searching for content type
			if (!buffer.compare("Content-Type: application/octet-stream")) {
				count++;
			} else {
				count = -1;
			}
			break;
		case 1:						// Searching for date
			if (!buffer.compare(0, 6, "Date: ")) {
				count++;
			} else {
				count = -1;
			}
			break;
		case 2:						// Searching for empty line
			if (buffer.size() == 0) {
				count++;
			} else {
				count = -1;
			}
			break;
		case 3:						// And now the content
            // TODO: encrypt buffer because that is crypted message
			chat = new QblJsonChat(buffer);

			count++;
			break;
		case 4:						// End of message
			if (buffer.at(0) == '-' && buffer.at(1) == '-') {
				count = 0;
				this->handleReceivedChatMessage(chat);
			} else {
				count = -1;
			}

			break;
		default:					// Error reading message
			break;
		}

		if (count == -1) {
			foundMsg = false;
		}
	}

	return (0);
}

int QblChatMessageReceive::handleReceivedChatMessage(QblJsonChat* chat)
{
    Qbl *qbl;
    QblMessage message;

    qbl = Qbl::getInstance();

    switch (chat->getType()) {
    case QblJsonChat::CHAT:
        if (chat->getSender().compare(this->identity->getAlias())) {
			Qbl *qbl;
			QblChatHistoryInternal *history;

			qbl = Qbl::getInstance();
			history = (QblChatHistoryInternal *)qbl->getChatHistory();
			history->addMessage(chat->getSender(), *chat);

            message = QblMessage(time(NULL), QblMessage::INFO,
                    QblMessage::CHAT, *chat);
            qbl->getSystemTrayMessages()->addMessage(message);
		} else {
			// TODO: Save own sended messages on different platforms
			// when a good history function is available
		}
        break;
    case QblJsonChat::UPLOAD_NEW_VERSION:
        message = QblMessage(time(NULL), QblMessage::DO,
                QblMessage::UPLOAD_NEW_VERSION, *chat);
        qbl->getSystemTrayMessages()->addMessage(message);
        break;
    case QblJsonChat::UPLOAD_NEW_VERSION_MAC:
        // Nothing to do because this client send this message
        if (qbl->getMac()->checkMacAddress(chat->getMac()) == true) {
            break;
        }
        message = QblMessage(time(NULL), QblMessage::DO,
                QblMessage::UPLOAD_NEW_VERSION_MAC, *chat);
        qbl->getSystemTrayMessages()->addMessage(message);
        break;
    default:
        std::string errmsg = "Unhandled chat message type";
        std::string errorNumber = std::to_string(chat->getType());
        throw QblException {
        errmsg, errorNumber};
    }

    return (0);
}
