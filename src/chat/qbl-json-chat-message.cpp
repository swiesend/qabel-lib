/*
 * @file        qbl-json-chat-message.cpp
 * @brief       Class to handle a real chat message (Implementation)
 * @author      Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-json-chat-message.h"

#include <fcntl.h>
#include <fcntl.h>
#include <json_object.h>
#include <linkhash.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "../qbl.h"
#include "qbl-json-object.h"

QblJsonChatMessage::QblJsonChatMessage()
{
    return;
}

QblJsonChatMessage::QblJsonChatMessage(json_object *obj) :
        QblJsonChat()
{
    this->parse(obj);

    return;
}

QblJsonChatMessage::QblJsonChatMessage(std::string sender, std::string message,
        time_t date) :
        QblJsonChat(sender, QblJsonChat::CHAT)
{
    this->setMessage(message);
    this->setMessageDate(date);

    return;
}

QblJsonChatMessage::~QblJsonChatMessage()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

std::string QblJsonChatMessage::getJsonString()
{
    std::string result;
    int i;

    result += QblJsonChat::getJsonString();

    result += "\"";
    result += this->elements[MESSAGE].name;
    result += "\":\"";
    result += *(std::string *) this->elements[MESSAGE].obj;
    result += "\",";
    result += "\"";
    result += this->elements[MESSAGE_DATE].name;
    result += "\":";
    result += to_string(*(time_t *) this->elements[MESSAGE_DATE].obj);
    result += ",";

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "}";

    return (result);
}

const std::string & QblJsonChatMessage::getMessage() const
{
    return (*((std::string *) this->elements[MESSAGE].obj));
}

void QblJsonChatMessage::setMessage(const std::string & message)
{
    this->elements[MESSAGE].obj = new std::string(message);

    return;
}

time_t QblJsonChatMessage::getMessageDate() const
{
    return (*((time_t *) this->elements[MESSAGE_DATE].obj));
}

void QblJsonChatMessage::setMessageDate(time_t messageDate)
{
    this->elements[MESSAGE_DATE].obj = new time_t(messageDate);
}

