/*
 * @file		qbl-chat-history.cpp
 * @brief		Class to handle chat history (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "qbl.h"
#include "qbl-chat-history.h"
#include "qbl-json-chat-array.h"
#include "qbl-json-chat-message-complete-array.h"
#include "qbl-config-file.h"

QblChatHistory::QblChatHistory() :
        listener(NULL)
{
    // TODO Auto-generated constructor stub

    return;
}

QblChatHistory::~QblChatHistory()
{
    // TODO Auto-generated destructor stub

    return;
}

void QblChatHistory::addListener(IQblChatReceive * listener)
{
    this->listener = listener;
}

void QblChatHistory::removeListener()
{
    this->listener = NULL;

    return;
}

void QblChatHistory::addContact(QblJsonMainConfigContact *contact)
{
    this->contactListener.push_back(contact);

    return;
}

std::list<QblJsonChatMessageComplete> QblChatHistory::getHistory(
        QblJsonMainConfigContact* contact)
{
    std::list<QblJsonChatMessageComplete> list;

    list = this->getHistoryList(contact->getAlias());

    return (list);
}

void QblChatHistory::removeContact(QblJsonMainConfigContact *contact)
{
    std::list<QblJsonMainConfigContact *>::iterator iterator;
    uint8_t retval;

    for (iterator = this->contactListener.begin();
            iterator != this->contactListener.end(); iterator++) {
        retval = (*iterator)->compare(contact);
        if (QblJsonObject::isUuidEqual(retval) == true) {
            this->contactListener.erase(iterator);
            break;
        }

    }

    return;
}

std::list<QblJsonChatMessageComplete>
    QblChatHistory::getHistoryList(std::string contact)
{
    std::list<QblJsonChatMessageComplete> result;
    std::string fileName;
    struct stat _stat;
    size_t length;
    int file, retval;
    uint8_t *buffer;
    std::string jsonStr;
    QblJsonChatMessageCompleteArray *json;
    std::list<QblJsonChatMessageComplete *> array;
    std::list<QblJsonChatMessageComplete *>::iterator iterator;
    std::list<QblJsonChatMessageComplete>::iterator resultIterator;
    bool foundOne;
    std::list<QblJsonMainConfigContact *> contactListener;
    std::list<QblJsonMainConfigContact *>::iterator contactIterator;

    fileName = QblConfigFile::getCacheChatDir() + "/" + contact;

    retval = stat(fileName.data(), &_stat);
    if (retval == -1) {
        if (errno == ENOENT) {
            return (result);
        }
    }
    length = _stat.st_size;

    buffer = (uint8_t *) malloc(length * sizeof(uint8_t));
    if (buffer == NULL) {
        std::string errmsg = "Cannot allocate memory";
        throw QblException { errmsg };
    }

    file = open(fileName.data(), O_RDONLY);
    if (file == -1) {
        std::string errmsg = "Error when opening file \"";
        errmsg += fileName;
        errmsg += "\"";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror (errno));
        free(buffer);
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    retval = read(file, buffer, length);
    if (retval < 0) {
        std::string errmsg = "Error read file \"";
        errmsg += fileName;
        errmsg += "\"";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror (errno));
        free(buffer);
        throw QblException { errmsg, errorNumber, errorDesc };
    }
    jsonStr = (char *) buffer;

    json = new QblJsonChatMessageCompleteArray();
    json->parse(jsonStr);
    array = json->getList();

    for (iterator = array.begin(); iterator != array.end(); iterator++) {
        foundOne = false;
        for (resultIterator = result.begin(); resultIterator != result.end();
                resultIterator++) {
            if (resultIterator->compare((*iterator))) {
                // integrate the entries
                switch ((*iterator)->getType()) {
                case QblJsonChat::CHAT:
                    ((QblJsonChatMessage) (*resultIterator)).integrate(*iterator);
                    break;
                //default:
                    // TODO to implement
                }

            }
        }

        if (foundOne == false) {
            result.push_back(**iterator);
        }
    }

    free(buffer);
    return (result);
}
