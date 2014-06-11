/*
 * @file		qbl-json-main-config-blockserver.cpp
 * @brief		Class to handle a block server in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config-blockserver.h"

QblJsonMainConfigBlockServer::QblJsonMainConfigBlockServer() :
        QblJson()
{

    return;
}


QblJsonMainConfigBlockServer::QblJsonMainConfigBlockServer(
        const std::string& server, int port, const std::string& path) :
        QblJson()
{
    this->setUrl(server, port, path);

    return;
}

QblJsonMainConfigBlockServer::~QblJsonMainConfigBlockServer()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
//        TODO free memory
    }

    return;
}

void QblJsonMainConfigBlockServer::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigBlockServer::parse(json_object *obj)
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

std::string QblJsonMainConfigBlockServer::getJsonString()
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

void QblJsonMainConfigBlockServer::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setServer(((QblJsonMainConfigBlockServer *) other)->getServer());
    this->setPort(((QblJsonMainConfigBlockServer *) other)->getPort());
    this->setPath(((QblJsonMainConfigBlockServer *) other)->getPath());
    this->setAuth(((QblJsonMainConfigBlockServer *) other)->getAuth());
    return;
}

const std::string& QblJsonMainConfigBlockServer::getServer() const
{
    return (*((std::string *) this->elements[SERVER].obj));
}

void QblJsonMainConfigBlockServer::setServer(const std::string& server)
{
    if(this->elements[SERVER].obj != &server) {
        ((std::string *)this->elements[SERVER].obj)->clear();
        ((std::string *)this->elements[SERVER].obj)->append(server);
    }
    return;
}

int QblJsonMainConfigBlockServer::getPort() const
{
    return (*((int *) this->elements[PORT].obj));
}

void QblJsonMainConfigBlockServer::setPort(int port)
{
    this->elements[PORT].obj = new int(port);
}

const std::string& QblJsonMainConfigBlockServer::getPath() const
{
    return (*((std::string *) this->elements[PATH].obj));
}

void QblJsonMainConfigBlockServer::setPath(const std::string& path)
{
    if(this->elements[PATH].obj != &path) {
        ((std::string *)this->elements[PATH].obj)->clear();
        ((std::string *)this->elements[PATH].obj)->append(path);
    }
    return;
}

void QblJsonMainConfigBlockServer::setUrl(const std::string& server, int port,
        const std::string& path)
{
    this->setServer(server);
    this->setPort(port);
    this->setPath(path);

    return;
}

std::string QblJsonMainConfigBlockServer::getUrl()
{
    std::string result;

    result.append(this->getServer()).append(":");
    result.append(std::to_string(this->getPort()));
    result.append(this->getPath());

    return (result);
}

const std::string& QblJsonMainConfigBlockServer::getAuth() const
{
    return (*((std::string *) this->elements[AUTH].obj));
}

void QblJsonMainConfigBlockServer::setAuth(const std::string& auth)
{ 
    if(this->elements[AUTH].obj != &auth) {
        ((std::string *)this->elements[AUTH].obj)->clear();
        ((std::string *)this->elements[AUTH].obj)->append(auth);
    }
    return;
}
