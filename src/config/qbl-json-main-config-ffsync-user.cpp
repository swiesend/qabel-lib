/*
 * @file		qbl-json-main-config-ffsync-user.cpp
 * @brief		Class to handle the firefox sync user in the main configuration (Implementation)
 * @author		Malte Zobel <zobel@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "qbl-json-main-config-ffsync-user.h"

QblJsonMainConfigFFSyncUser::QblJsonMainConfigFFSyncUser() :
        QblJson()
{

    return;
}

QblJsonMainConfigFFSyncUser::~QblJsonMainConfigFFSyncUser()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory?
    }

    return;
}

void QblJsonMainConfigFFSyncUser::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigFFSyncUser::parse(json_object *obj)
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
            if(this->elements[i].type == json_type_string) {
                ((std::string *) this->elements[i].obj)->clear();
                ((std::string *) this->elements[i].obj)->append(
                    json_object_get_string(value));
            }
            else if(this->elements[i].type == json_type_boolean) {
                this->elements[i].obj = new bool(json_object_get_boolean(value));
            }
            else if(this->elements[i].type == json_type_int) {
                this->elements[i].obj = new int(json_object_get_int(value));
            }
            else if(this->elements[i].type == json_type_double) {
                this->elements[i].obj = new double(json_object_get_double(value));
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
        if (this->elements[i].checked == false) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    return;
}

std::string QblJsonMainConfigFFSyncUser::getJsonString()
{
    std::string result;
    int i;
    result += QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        result += "\n\t\t";
        result += QblJson::getJsonString(&this->elements[i]);
        result += ",";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "\n\t";

    return (result);
}

void QblJsonMainConfigFFSyncUser::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setUsername(((QblJsonMainConfigFFSyncUser *)other)->getUsername());
    this->setMail(((QblJsonMainConfigFFSyncUser *)other)->getMail());
    this->setPassword(((QblJsonMainConfigFFSyncUser *)other)->getPassword());
    this->setUrl(((QblJsonMainConfigFFSyncUser *)other)->getUrl());
    this->setPort(((QblJsonMainConfigFFSyncUser *)other)->getPort());
    this->setInterval(((QblJsonMainConfigFFSyncUser *)other)->getInterval());
    this->setKey(((QblJsonMainConfigFFSyncUser *)other)->getKey());
    this->setModified(((QblJsonMainConfigFFSyncUser *)other)->getModified());
    return;
}

const std::string& QblJsonMainConfigFFSyncUser::getUsername() const {
    return (*((std::string*) this->elements[USERNAME].obj));
}

void QblJsonMainConfigFFSyncUser::setUsername(const std::string& value) {
    this->elements[USERNAME].obj = new std::string(value);
}

const std::string& QblJsonMainConfigFFSyncUser::getMail() const {
    return (*((std::string*) this->elements[MAIL].obj));
}

void QblJsonMainConfigFFSyncUser::setMail(const std::string& value) {
    this->elements[MAIL].obj = new std::string(value);
}

const std::string& QblJsonMainConfigFFSyncUser::getPassword() const {
    return (*((std::string*) this->elements[PASSWORD].obj));
}

void QblJsonMainConfigFFSyncUser::setPassword(const std::string& value) {
    this->elements[PASSWORD].obj = new std::string(value);
}

const std::string& QblJsonMainConfigFFSyncUser::getUrl() const {
    return (*((std::string*) this->elements[URL].obj));
}

void QblJsonMainConfigFFSyncUser::setUrl(const std::string& value) {
    this->elements[URL].obj = new std::string(value);
}

int QblJsonMainConfigFFSyncUser::getPort() const {
    return (*((int*) this->elements[PORT].obj));
}

void QblJsonMainConfigFFSyncUser::setPort(const int value) {
    this->elements[PORT].obj = new int(value);
}

const std::string& QblJsonMainConfigFFSyncUser::getKey() const {
    return (*((std::string*) this->elements[KEY].obj));
}

void QblJsonMainConfigFFSyncUser::setKey(const std::string& value) {
    this->elements[KEY].obj = new std::string(value);
}

int QblJsonMainConfigFFSyncUser::getInterval() const {
    return (*((int*) this->elements[INTERVAL].obj));
}

void QblJsonMainConfigFFSyncUser::setInterval(const int value) {
    this->elements[INTERVAL].obj = new int(value);
}

double QblJsonMainConfigFFSyncUser::getModified() const {
    return (*((double*) this->elements[MODIFIED].obj));
}

void QblJsonMainConfigFFSyncUser::setModified(const double value) {
    this->elements[MODIFIED].obj = new double(value);
}

