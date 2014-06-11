/*
 * @file		qbl-json-chat-message-complete-array.cpp
 * @brief		Class to handle an array of complete chat messages (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-chat-message-complete-array.h"
#include "qbl-json-chat.h"

QblJsonChatMessageCompleteArray::QblJsonChatMessageCompleteArray() :
        QblJsonArray()
{

    return;
}

QblJsonChatMessageCompleteArray::~QblJsonChatMessageCompleteArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    }

    return;
}

void QblJsonChatMessageCompleteArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonChatMessageCompleteArray::parse(json_object *obj)
{
    if (obj != NULL) {
        this->obj = obj;
    }

    json_object_object_foreach(this->obj, key, value) {
        int i, length;
        json_object *child;

        length = json_object_array_length(value);
        for (i = 0; i < length; i++) {
            QblJsonChatMessageComplete *contact;

            child = json_object_array_get_idx(value, i);
            contact = new QblJsonChatMessageComplete(child);
            this->list.push_back((QblJsonObject *) contact);
        }
    }

    return;
}

std::string QblJsonChatMessageCompleteArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"chat\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonChatMessageComplete *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "]";

    return (result);
}

void QblJsonChatMessageCompleteArray::integrate(QblJson* /*other*/)
{

    return;
}

std::list<QblJsonChatMessageComplete *> QblJsonChatMessageCompleteArray::getList()
{
    std::list<QblJsonChatMessageComplete *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonChatMessageComplete*) *iterator);
    }

    return (result);
}
