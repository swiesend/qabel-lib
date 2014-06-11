/*
 * @file		qbl-json-main-config-blockserver-array.cpp
 * @brief		Class to handle the block server array in the main configuration
 *              (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *      		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-blockserver-array.h"

QblJsonMainConfigBlockServerArray::QblJsonMainConfigBlockServerArray():
    QblJsonArray()
{

    return;
}

QblJsonMainConfigBlockServerArray::~QblJsonMainConfigBlockServerArray()
{
    std::list<QblJsonObject*>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
         iterator++) {
        // TODO free memory
    }

    return;
}

void QblJsonMainConfigBlockServerArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigBlockServerArray::parse(json_object * obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigBlockServer *blockServer;

        value = json_object_array_get_idx(obj, i);
        blockServer = new QblJsonMainConfigBlockServer();
        blockServer->parse(value);
        this->list.push_back((QblJsonObject *) blockServer);
    }

    return;
}

std::string QblJsonMainConfigBlockServerArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject*>::iterator iterator;

    result = "\"block_servers\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
         iterator++) {
        result += "{";
        result +=
            ((QblJsonMainConfigBlockServer *) (*iterator))->
            getJsonString();
        result += "},";
    }

    // Remove last comma
    if (this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigBlockServerArray::integrate(QblJson * /*other */ )
{
    return;
}

std::list<QblJsonMainConfigBlockServer *>
    QblJsonMainConfigBlockServerArray::getList()
{
    QblJsonMainConfigBlockServerList result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
         iterator++) {
        result.push_back((QblJsonMainConfigBlockServer *) * iterator);
    }

    return (result);
}

QblJsonMainConfigBlockServer
    *QblJsonMainConfigBlockServerArray::getItem(int64_t id)
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
         iterator++) {
        if ((*iterator)->getUuid() == id) {
            return ((QblJsonMainConfigBlockServer *) * iterator);
        }
    }

    return (NULL);
}
