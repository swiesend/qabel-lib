/*
 * @file		qbl-json-main-config-upload.cpp
 * @brief		Class to handle an upload in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config-upload.h"

QblJsonMainConfigUpload::QblJsonMainConfigUpload() :
        QblJson()
{

    return;
}

QblJsonMainConfigUpload::~QblJsonMainConfigUpload()
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
    }

    return;
}

void QblJsonMainConfigUpload::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigUpload::parse(json_object *obj)
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
                ((std::string *) this->elements[i].obj)->clear();
                ((std::string *) this->elements[i].obj)->append(
                        json_object_get_string(value));
            } else if (this->elements[i].type == json_type_boolean) {
                *((bool*)this->elements[i].obj) =
                        json_object_get_boolean(value);
            } else if (this->elements[i].type == json_type_int) {
                *((int*)this->elements[i].obj) = json_object_get_int(value);
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

std::string QblJsonMainConfigUpload::getJsonString()
{
    std::string result;
    int i;

    result = QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        result += QblJson::getJsonString(&this->elements[i]);
        result += ",";
    }

    // Remove last comma
    return (result.substr(0, result.size() - 1));
}

void QblJsonMainConfigUpload::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

	this->setBlockServerId(((QblJsonMainConfigUpload *)other)->getBlockServerId());
	this->setPublic(((QblJsonMainConfigUpload *)other)->getPublic());

    return;
}

int QblJsonMainConfigUpload::getBlockServerId() const
{
    return (*((int*) this->elements[BLOCK_SERVER_ID].obj));
}

const std::string& QblJsonMainConfigUpload::getPublic() const
{
    return (*((std::string *) this->elements[PUBLIC].obj));
}

void QblJsonMainConfigUpload::setBlockServerId(const int value)
{
    *((int *)this->elements[BLOCK_SERVER_ID].obj) = value;

    return;
}

void QblJsonMainConfigUpload::setPublic(const std::string& value)
{
    if(this->elements[PUBLIC].obj != &value) {
        ((std::string *)this->elements[PUBLIC].obj)->clear();
        ((std::string *)this->elements[PUBLIC].obj)->append(value);
    }
    return;
}

const std::string& QblJsonMainConfigUpload::getToken() const
{
    return (*((std::string *) this->elements[TOKEN].obj));
}

void QblJsonMainConfigUpload::setToken(const std::string& value)
{
    if(this->elements[TOKEN].obj != &value) {
        ((std::string *)this->elements[TOKEN].obj)->clear();
        ((std::string *)this->elements[TOKEN].obj)->append(value);
    }
    return;
}

const std::string& QblJsonMainConfigUpload::getRevokeToken() const
{
    return (*((std::string *) this->elements[REVOKE_TOKEN].obj));
}

void QblJsonMainConfigUpload::setRevokeToken(const std::string& value)
{
    if(this->elements[REVOKE_TOKEN].obj != &value) {
        ((std::string *)this->elements[REVOKE_TOKEN].obj)->clear();
        ((std::string *)this->elements[REVOKE_TOKEN].obj)->append(value);
    }
    return;
}
