/*
 * @file		qbl-json-block-storage-new.cpp
 * @brief		Class to handle the received storage request JSON configuration
 *              (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json-block-storage-new.h"

QblJsonBlockStorageNew::QblJsonBlockStorageNew() : QblJson()
{

    return;
}

QblJsonBlockStorageNew::~QblJsonBlockStorageNew()
{

    return;
}

void QblJsonBlockStorageNew::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonBlockStorageNew::parse(json_object *obj)
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
            ((std::string *) this->elements[i].obj)->append(
                    json_object_get_string(value));

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

    };

    /**
     * Check whether everything is set
     */
    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (this->elements[i].mandatory == true
                && this->elements[i].checked == false) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    return;
}

std::string QblJsonBlockStorageNew::getJsonString()
{
    std::string result;

    return (result);
}

void QblJsonBlockStorageNew::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setPublic(((QblJsonBlockStorageNew *)other)->getPublic());
    this->setToken(((QblJsonBlockStorageNew *)other)->getToken());
    this->setRevokeToken(((QblJsonBlockStorageNew *)other)->getRevokeToken());

    return;
}

const std::string& QblJsonBlockStorageNew::getPublic() const
{
    return (*((std::string *) this->elements[PUBLIC].obj));
}

void QblJsonBlockStorageNew::setPublic(const std::string& _public)
{
    this->elements[PUBLIC].obj = new std::string(_public);

    return;
}

const std::string& QblJsonBlockStorageNew::getToken() const
{
    return (*((std::string *) this->elements[TOKEN].obj));
}

void QblJsonBlockStorageNew::setToken(const std::string& token)
{
    this->elements[TOKEN].obj = new std::string(token);

    return;
}

const std::string& QblJsonBlockStorageNew::getRevokeToken() const
{
    return (*((std::string *) this->elements[REVOKE_TOKEN].obj));
}

void QblJsonBlockStorageNew::setRevokeToken(const std::string& revokeToken)
{
    this->elements[REVOKE_TOKEN].obj = new std::string(revokeToken);

    return;
}

