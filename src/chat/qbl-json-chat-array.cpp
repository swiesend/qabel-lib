/*
 * @file		qbl-json-chat-array.cpp
 * @brief		Class to handle the chat messages (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-chat-array.h"
#include "qbl-json-chat.h"

QblJsonChatArray::QblJsonChatArray() :
        QblJsonArray()
{

    return;
}

QblJsonChatArray::~QblJsonChatArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {

    }

    return;
}

void QblJsonChatArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonChatArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    if (obj != NULL) {
        this->obj = obj;
    }

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonChat *contact;

        value = json_object_array_get_idx(obj, i);
        contact = new QblJsonChat(value);
        this->list.push_back((QblJsonObject *) contact);
    }

    return;
}

std::string QblJsonChatArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"chat\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonChat *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "]";

    return (result);
}

void QblJsonChatArray::integrate(QblJson* /*other*/)
{

    return;
}

std::list<QblJsonChat *> QblJsonChatArray::getList()
{
    std::list<QblJsonChat *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonChat*) *iterator);
    }

    return (result);
}
