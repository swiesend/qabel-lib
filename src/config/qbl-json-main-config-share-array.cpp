/*
 * @file		qbl-json-main-config-share-array.cpp
 * @brief		Class to handle the share array in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-share-array.h"

QblJsonMainConfigShareArray::QblJsonMainConfigShareArray() :
        QblJsonArray()
{
    return;
}

QblJsonMainConfigShareArray::~QblJsonMainConfigShareArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory
    }

    return;
}

void QblJsonMainConfigShareArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigShareArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigShare *share;

        value = json_object_array_get_idx(obj, i);
        share = new QblJsonMainConfigShare();
        share->parse(value);
        this->list.push_back((QblJsonObject *) share);
    }

    return;
}

std::string QblJsonMainConfigShareArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"shares\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigShare *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigShareArray::integrate(QblJson* /*other*/)
{
    return;
}

std::list<QblJsonMainConfigShare *> QblJsonMainConfigShareArray::getList()
{
    std::list<QblJsonMainConfigShare *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigShare *) *iterator);
    }

    return (result);
}

