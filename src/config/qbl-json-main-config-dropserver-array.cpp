/*
 * @file		qbl-json-main-config-dropserver-array.cpp
 * @brief		Class to handle the drop server array in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-dropserver-array.h"

QblJsonMainConfigDropServerArray::QblJsonMainConfigDropServerArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigDropServerArray::~QblJsonMainConfigDropServerArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory
    }

    return;
}

void QblJsonMainConfigDropServerArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigDropServerArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigDropServer *dropServer;

        value = json_object_array_get_idx(obj, i);
        dropServer = new QblJsonMainConfigDropServer();
        dropServer->parse(value);
        this->list.push_back((QblJsonObject *) dropServer);
    }

    return;
}

std::string QblJsonMainConfigDropServerArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"drop_servers\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigDropServer *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigDropServerArray::integrate(QblJson* /*other*/)
{
    return;
}

std::list<QblJsonMainConfigDropServer *> QblJsonMainConfigDropServerArray::getList()
{
    std::list<QblJsonMainConfigDropServer *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigDropServer*) *iterator);
    }

    return (result);
}

