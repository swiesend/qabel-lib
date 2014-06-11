/*
 * @file		qbl-json-main-config-share.cpp
 * @brief		Class to handle a share in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config-share.h"

QblJsonMainConfigShare::QblJsonMainConfigShare() :
        QblJson()
{

    return;
}

QblJsonMainConfigShare::~QblJsonMainConfigShare()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (this->elements[i].type == json_type_string) {
            delete ((std::string *) this->elements[i].obj);
        }
        else if (this->elements[i].type == json_type_boolean) {
            delete ((bool *) this->elements[i].obj);           
        }
        else if (this->elements[i].type == json_type_int) {
            delete ((int *) this->elements[i].obj);
        }
        else if(this->elements[i].type == json_type_double) {
            delete ((double *) this->elements[i].obj);
        }
        else if(this->elements[i].type == json_type_array) {
            delete ((std::list<int> *) this->elements[i].obj);
        }
    }

    return;
}

void QblJsonMainConfigShare::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigShare::parse(json_object *obj)
{
    int i;
    bool foundOne;

    if (obj != NULL) {
        this->obj = obj;
    }

    json_object_object_foreach(this->obj, key, value) {
        foundOne = false;
        for (i = 0;
                i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
                i++) {
            if (strcmp(this->elements[i].name, key)) {
                continue;
            }
            foundOne = true;

            if (this->elements[i].checked == true) {
                throw QblJsonException("Element \"%s\" already exists\n", key);
            }
            if (this->elements[i].type != json_object_get_type(value)) {
                throw QblJsonException("Element \"%s\" have wrong type\n", key);
            }
            this->elements[i].checked = true;
            if (this->elements[i].type == json_type_string) {
                ((std::string *) this->elements[i].obj)->append(
                        json_object_get_string(value));
            } else if (this->elements[i].type == json_type_boolean) {
                this->elements[i].obj = new bool(
                        json_object_get_boolean(value));
            } else if (this->elements[i].type == json_type_int) {
                this->elements[i].obj = new int(json_object_get_int(value));
            } else if (this->elements[i].type == json_type_array) {
                this->parseContactArray(value);
            }

            break;
        }

        if (foundOne == false) {
            bool retval;

            retval = QblJsonObject::parse(key, value);
            if (retval == false) {
                throw QblJsonException("Element \"%s\" is not allowed here\n",
                        key);
            }
        }
    }

    /**
     * Check whether everything is set
     */
    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (this->elements[i].mandatory == true) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    return;
}

std::string QblJsonMainConfigShare::getJsonString()
{
    std::string result;
    int i;

    result = QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (i == CONTACTS) {
            int j, count;
            std::list<int> *list;
            std::list<int>::iterator iterator;

            result += "\"";
            result += this->elements[i].name;
            result += "\": [";

            list = ((std::list<int> *) this->elements[CONTACTS].obj);
            for (iterator = list->begin(); iterator != list->end();
                    iterator++) {
                result += std::to_string(*iterator);
                result += ",";
            }
            result.resize(result.size() - 1);
            result += "]";
        } else {
            result += QblJson::getJsonString(&this->elements[i]);
        }
        result += ",";
    }

    // Remove last comma
    return (result.substr(0, result.size() - 1));
}

void QblJsonMainConfigShare::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setBasedir(((QblJsonMainConfigShare *) other)->getBasedir());
    return;
}

const std::string& QblJsonMainConfigShare::getBasedir() const
{
    return (*((std::string *) this->elements[BASEDIR].obj));
}

void QblJsonMainConfigShare::setBasedir(const std::string& basedir)
{
    if(this->elements[BASEDIR].obj != &basedir) {
        ((std::string *)this->elements[BASEDIR].obj)->clear();
        ((std::string *)this->elements[BASEDIR].obj)->append(basedir);
    }
    return;
}

int QblJsonMainConfigShare::getUploadId() const
{
    return (*((int *) this->elements[UPLOAD_ID].obj));
}

void QblJsonMainConfigShare::setUploadId(const int uploadId)
{
    *((int*)this->elements[UPLOAD_ID].obj) = uploadId;
}

int QblJsonMainConfigShare::getAliasId() const
{
    return (*((int *) this->elements[ALIAS_ID].obj));
}

void QblJsonMainConfigShare::setAliasId(const int aliasId)
{
    *((int*)this->elements[ALIAS_ID].obj) = aliasId;
}

std::list<int> *QblJsonMainConfigShare::getContacts() const
{
    return ((std::list<int> *) this->elements[CONTACTS].obj);
}

void QblJsonMainConfigShare::setContacts(std::list<int> contacts)
{
    std::list<int>::iterator iterator;

    ((std::list<int> *) this->elements[CONTACTS].obj)->clear();
    for (iterator = contacts.begin(); iterator != contacts.end(); iterator++) {
        ((std::list<int> *) this->elements[CONTACTS].obj)->push_back(*iterator);
    }
}

const std::string& QblJsonMainConfigShare::getKey() const
{
    return (*((std::string *) this->elements[KEY].obj));
}

void QblJsonMainConfigShare::setKey(const std::string& key)
{
    if(this->elements[KEY].obj != &key) {
        ((std::string *)this->elements[KEY].obj)->clear();
        ((std::string *)this->elements[KEY].obj)->append(key);
    }
    return;
}

void QblJsonMainConfigShare::parseContactArray(json_object* obj)
{
    int i, length, uuid;
    json_object *value;

    ((std::list<int> *) this->elements[CONTACTS].obj)->clear();
    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {

        value = json_object_array_get_idx(obj, i);
        uuid = json_object_get_int(value);
        ((std::list<int> *) this->elements[CONTACTS].obj)->push_back(uuid);
    }

    return;
}
