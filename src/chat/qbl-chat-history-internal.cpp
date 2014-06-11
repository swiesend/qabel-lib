/*
 * @file		qbl-chat-history-internal.cpp
 * @brief		Internal library class to handle chat history (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-chat-history-internal.h"

#include <errno.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <list>
#include <mutex>
#include <string>
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "qbl.h"
#include "qbl-config-file.h"
#include "qbl-json-main-config-contact.h"
#include "qbl-json-chat-message.h"
#include "qbl-json-chat-array.h"
#include "iqbl-chat-receive.h"

#define JSON_HEADER "{\"chat\":["
#define JSON_FOOTER "]}"
#define COMMA ","

QblChatHistoryInternal::QblChatHistoryInternal()
{
    // TODO Auto-generated constructor stub

    return;
}

QblChatHistoryInternal::~QblChatHistoryInternal()
{
    // TODO Auto-generated destructor stub

    return;
}

void QblChatHistoryInternal::addMessage(std::string contactAlias,
        QblJsonChat chat)
{
    std::lock_guard<std::mutex> guard(mutex);

    this->list.push_back(QblChatHistoryPair(contactAlias, chat));

    return;
}

void QblChatHistoryInternal::handleMessage()
{
    if (this->list.size() > 0) {
        std::list<QblChatHistoryPair>::iterator iterator;
        std::string jsonStr, contact;
        bool saveHistory = false;

        std::lock_guard<std::mutex> guard(mutex);

        iterator = this->list.begin();
        contact = iterator->first;
        QblJsonChat chat = iterator->second;
        jsonStr = iterator->second.getJsonString();
        switch (chat.getType()) {
        case QblJsonChat::CHAT:     /* normal chat message */
        {
            QblJsonChatMessage buffer(*(QblJsonChatMessage*) &chat);

            jsonStr = buffer.getJsonString();
            saveHistory = true;
            break;
        }
        default:
            std::string errmsg = "Unhandled chat message type";
            std::string errorNumber = std::to_string(chat.getType());
            throw QblException { errmsg, errorNumber };
        }

        if (saveHistory == true) {
            std::list<QblJsonMainConfigContact *>::iterator contactIterator;

            this->saveMessageToHistory(contact, jsonStr);

            for (contactIterator = this->contactListener.begin();
                    contactIterator != this->contactListener.end();
                    contactIterator++) {
                if (!contact.compare((*contactIterator)->getAlias())) {
                }
            }
        }

        this->list.erase(iterator);
    }

    return;
}

void QblChatHistoryInternal::saveMessageToHistory(std::string contact,
        std::string jsonStr)
{
    std::string fileName;
    struct stat _stat;
    int retval, file;

    fileName = QblConfigFile::getCacheChatDir() + "/" + contact;

    retval = stat(fileName.data(), &_stat);
    if (retval != 0) {
        // Create new file
        if (errno == ENOENT) {
            file = open(fileName.data(), O_WRONLY | O_CREAT,
            S_IWRITE | S_IREAD);
            if (file == -1) {
                // TODO: Send error to GUI
                return;
            }
            retval = write(file, JSON_HEADER, strlen(JSON_HEADER));
            if (retval == -1) {
                // TODO: Send error to GUI

                return;
            }
            retval = write(file, jsonStr.data(), jsonStr.length());
            if (retval == -1) {
                // TODO: Send error to GUI

                return;
            }
            retval = write(file, JSON_FOOTER, strlen(JSON_FOOTER));
            if (retval == -1) {
                // TODO: Send error to GUI

                return;
            }

            close(file);
        } else {

        }
    } else {
        file = open(fileName.data(), O_WRONLY);
        if (file == -1) {
            // TODO: Send error to GUI
            return;
        }
        retval = lseek(file, -2L, SEEK_END);
        if (retval == -1) {
            // TODO: Send error to GUI
            return;
        }
        retval = write(file, COMMA, strlen(COMMA));
        if (retval == -1) {
            // TODO: Send error to GUI

            return;
        }
        retval = write(file, jsonStr.data(), jsonStr.length());
        if (retval == -1) {
            // TODO: Send error to GUI

            return;
        }
        retval = write(file, JSON_FOOTER, strlen(JSON_FOOTER));
        if (retval == -1) {
            // TODO: Send error to GUI
            return;
        }
        close(file);
    }

    this->createHistoryList(contact);

    return;
}

void QblChatHistoryInternal::createHistoryList(std::string contact)
{
    std::list<QblJsonChatMessageComplete> list;
    std::list<QblJsonMainConfigContact *>::iterator contactIterator;

    list = this->getHistoryList(contact);

    for (contactIterator = this->contactListener.begin();
            contactIterator != this->contactListener.end(); contactIterator++) {
        if (! contact.compare((*contactIterator)->getAlias())) {
            this->listener->messageReceived(contact, list);
        }
    }

    return;
}
