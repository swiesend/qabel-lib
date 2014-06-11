/*
 * @file		qbl-json-array.cpp
 * @brief		Main Class for a JSON array (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <json_tokener.h>
#include <string.h>

#include "qbl-json-array.h"

#define BUFFER_LENGTH 1024

QblJsonArray::QblJsonArray() :
        QblJson()
{

    return;
}

QblJsonArray::~QblJsonArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    if (this->list.size() > 0) {
        for (iterator = this->list.begin(); iterator != this->list.end();
                iterator++) {
            delete (*iterator);
        }

        this->list.clear();
    }

    return;
}

QblJsonObject *QblJsonArray::deleteEntry(QblJsonObject* obj)
{
    QblJsonObject *result = NULL;
    std::list<QblJsonObject *>::iterator iterator;
    uint8_t compare;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        compare = obj->compare(*iterator);
        if (this->isUuidEqual(compare)) {
            result = *iterator;
            this->list.erase(iterator);
            break;

        }
    }

    return (result);
}

QblJsonObject *QblJsonArray::findObject(QblJsonObject *obj) {
    uint8_t compareResult;
    for(std::list<QblJsonObject *>::iterator iterator = this->list.begin();
        iterator != this->list.end();
        iterator++) {
        compareResult = obj->compare((QblJsonObject*)(*iterator));
        if(obj->isUuidEqual(compareResult)) {
            return ((QblJsonObject*)(*iterator));
        }
    }
    return NULL;
}

void QblJsonArray::addEntry(QblJsonObject* obj)
{
    this->list.push_back(obj);

    return;
}
