/*
 * @file		qbl-json-main-config-account.cpp
 * @brief		Class to handle the accounts in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-account-array.h"

QblJsonMainConfigAccountArray::QblJsonMainConfigAccountArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigAccountArray::~QblJsonMainConfigAccountArray()
{

    return;
}

void QblJsonMainConfigAccountArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigAccountArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigAccount *account;

        value = json_object_array_get_idx(obj, i);
        account = new QblJsonMainConfigAccount();
        account->parse(value);
        this->list.push_back((QblJsonObject *) account);
    }

    return;
}

std::string QblJsonMainConfigAccountArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result += "\"accounts\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigAccount *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigAccountArray::integrate(QblJson* /*other*/)
{

    return;
}

std::list<QblJsonMainConfigAccount *> QblJsonMainConfigAccountArray::getList()
{
    std::list<QblJsonMainConfigAccount *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigAccount *) *iterator);
    }

    return (result);
}
