/*
 * @file		qbl-json-main-config-upload-array.cpp
 * @brief		Class to handle the upload array in the main configuration
 *  (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *      		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-upload-array.h"

QblJsonMainConfigUploadArray::QblJsonMainConfigUploadArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigUploadArray::~QblJsonMainConfigUploadArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory
    }

    return;
}

void QblJsonMainConfigUploadArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigUploadArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigUpload *upload;

        value = json_object_array_get_idx(obj, i);
        upload = new QblJsonMainConfigUpload();
        upload->parse(value);
        this->list.push_back((QblJsonObject *) upload);
    }

    return;
}

std::string QblJsonMainConfigUploadArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"uploads\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigUpload *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigUploadArray::integrate(QblJson* /*other*/)
{
    return;
}

QblJsonMainConfigUploadList QblJsonMainConfigUploadArray::getList()
{
    std::list<QblJsonMainConfigUpload *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigUpload *) *iterator);
    }

    return (result);
}

QblJsonMainConfigUpload* QblJsonMainConfigUploadArray::getItem(int64_t id)
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        if ((*iterator)->getUuid() == id) {
            return ((QblJsonMainConfigUpload *) *iterator);
        }
    }

    return (NULL);
}
