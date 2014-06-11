/*
 * @file		qbl-json-main-config-dropserver.cpp
 * @brief		Class to handle a drop server in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config-dropserver.h"

QblJsonMainConfigDropServer::QblJsonMainConfigDropServer() :
        QblJson()
{

    return;
}

QblJsonMainConfigDropServer::~QblJsonMainConfigDropServer()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
//        TODO free memory
    }

    return;
}

void QblJsonMainConfigDropServer::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigDropServer::parse(json_object *obj)
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
                ((std::string *) this->elements[i].obj)->append(
                    json_object_get_string(value));
            }
            else if(this->elements[i].type == json_type_boolean) {
                this->elements[i].obj = new bool(json_object_get_boolean(value));
            }
            else if(this->elements[i].type == json_type_int) {
                this->elements[i].obj = new bool(json_object_get_int(value));
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

std::string QblJsonMainConfigDropServer::getJsonString()
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

void QblJsonMainConfigDropServer::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setUrl(((QblJsonMainConfigDropServer *)other)->getUrl());
    this->setAuth(((QblJsonMainConfigDropServer *)other)->getAuth());
    this->setActive(((QblJsonMainConfigDropServer *)other)->getActive());
    this->setWebSockets(((QblJsonMainConfigDropServer *)other)->getWebSockets());
    this->setPollInterval(((QblJsonMainConfigDropServer *)other)->getPollInterval());
    return;
}

const std::string& QblJsonMainConfigDropServer::getUrl() const{
    return (*((std::string *) this->elements[URL].obj));
}

void QblJsonMainConfigDropServer::setUrl(const std::string& url) {
    if(this->elements[URL].obj != &url) {
        ((std::string *)this->elements[URL].obj)->clear();
        ((std::string *)this->elements[URL].obj)->append(url);
    }
    return;
}

const std::string& QblJsonMainConfigDropServer::getAuth() const{
    return (*((std::string *) this->elements[AUTH].obj));
}

void QblJsonMainConfigDropServer::setAuth(const std::string& auth) {
    if(this->elements[AUTH].obj != &auth) {
        ((std::string *)this->elements[AUTH].obj)->clear();
        ((std::string *)this->elements[AUTH].obj)->append(auth);
    }
    return;
}

bool QblJsonMainConfigDropServer::getActive() const {
    return (*((bool*) this->elements[ACTIVE].obj));
}

void QblJsonMainConfigDropServer::setActive(const bool value) {
    *((bool*)this->elements[ACTIVE].obj) = new bool(value);
}

bool QblJsonMainConfigDropServer::getWebSockets() const {
    return (*((bool*) this->elements[WEBSOCKETS].obj));
}

void QblJsonMainConfigDropServer::setWebSockets(const bool value) {
    *((bool*)this->elements[WEBSOCKETS].obj) = value;
}


int QblJsonMainConfigDropServer::getPollInterval() const {
    return (*((int*) this->elements[POLL_INTERVAL].obj));
}

void QblJsonMainConfigDropServer::setPollInterval (const int value) {
    *((int*)this->elements[POLL_INTERVAL].obj) = value;
    return;
}
