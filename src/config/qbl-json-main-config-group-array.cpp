/*
 * @file		qbl-json-main-config-group-array.cpp
 * @brief		Class to handle the group array in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-group-array.h"

QblJsonMainConfigGroupArray::QblJsonMainConfigGroupArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigGroupArray::~QblJsonMainConfigGroupArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory
    }

    return;
}

void QblJsonMainConfigGroupArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigGroupArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigGroup *group;

        value = json_object_array_get_idx(obj, i);
        group = new QblJsonMainConfigGroup();
        group->parse(value);
        this->list.push_back((QblJsonObject *) group);
    }

    return;
}

std::string QblJsonMainConfigGroupArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"groups\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigGroup *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigGroupArray::integrate(QblJson* /*other*/)
{
    return;
}

std::list<QblJsonMainConfigGroup *> QblJsonMainConfigGroupArray::getList()
{
    std::list<QblJsonMainConfigGroup *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigGroup *) *iterator);
    }

    return (result);
}

