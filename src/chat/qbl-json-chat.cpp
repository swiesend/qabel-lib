/*
 * @file        qbl-json-chat.cpp
 * @brief       Class to handle a chat message (Implementation)
 * @author      Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-json-chat.h"

#include <fcntl.h>
#include <fcntl.h>
#include <json_object.h>
#include <linkhash.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "../qbl.h"
#include "qbl-json-object.h"

QblJsonChat::QblJsonChat()
{
    return;
}

QblJsonChat::QblJsonChat(std::string jsonString) :
        QblJson()
{
    this->parse(jsonString);

    this->setSendState(true);

    return;
}

QblJsonChat::QblJsonChat(std::string sender, messageType type) :
        QblJson()
{
    this->setSender(sender);
    this->setType(type);
    this->setSendState(true);

    return;
}

QblJsonChat::QblJsonChat(std::string sender, std::string fileName,
        std::string key) :
        QblJson()
{
    std::ifstream stream;
    int retval, file;
    struct stat _stat;
    uint8_t *buffer;
    size_t length;
    bool foundError = false;
    std::ostringstream stm;

    this->setSender(sender);
    this->setMessage("");
    this->setFileName(fileName);
    this->setKey(key);
    this->setSendState(true);

    retval = stat(fileName.data(), &_stat);
    if (retval != 0) {
        foundError = true;
        std::string errmsg = "File \"";
        errmsg += this->getFileName();
        errmsg += "\" does not exists";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror (errno));
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    length = _stat.st_size;
    buffer = (uint8_t *) malloc(length * sizeof(uint8_t));
    if (buffer == NULL) {
        foundError = true;
        std::string errmsg = "Cannot allocate memory";
        throw QblException { errmsg };
    }

    file = open(fileName.data(), O_RDONLY);
    if (file == -1) {
        foundError = true;
        std::string errmsg = "Error when opening file \"";
        errmsg += this->getFileName();
        errmsg += "\"";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror (errno));
        free(buffer);
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    retval = read(file, buffer, length);
    if (retval < 0) {
        foundError = true;
        std::string errmsg = "Error read file \"";
        errmsg += this->getFileName();
        errmsg += "\"";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror (errno));
        free(buffer);
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    for (size_t i = 0; i < length; i++) {
        stm << std::setw(2) << std::setfill('0') << std::hex << std::nouppercase
                << (int) buffer[i];
    }
    if (foundError == true) {
        this->setFile("");
    } else {
        this->setFile(stm.str());
    }
    free(buffer);

    return;
}

QblJsonChat::QblJsonChat(json_object* obj)
{
    this->parse(obj);

    return;
}

QblJsonChat::~QblJsonChat()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

void QblJsonChat::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonChat::parse(json_object * obj)
{
    int i;
    bool foundOne;

    if (obj != NULL) {
        this->obj = obj;
    }

    json_object_object_foreach(this->obj, key, value) {
        this->parse(key, value);
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

bool QblJsonChat::parse(char *key, json_object* value)
{
    bool result;
    int i;

    result = false;
    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (strcmp(this->elements[i].name, key)) {
            continue;
        }
        result = true;

        if (this->elements[i].checked == true) {
            throw QblJsonException("Element \"%s\" already exists\n", key);
        }
        if (this->elements[i].type != json_object_get_type(value)) {
            throw QblJsonException("Element \"%s\" have wrong type\n", key);
        }
        this->elements[i].checked = true;

        if (this->elements[i].type == json_type_string) {
            this->elements[i].obj =
                new std::string(json_object_get_string(value));
        } else if (this->elements[i].type == json_type_boolean) {
            this->elements[i].obj = new bool(json_object_get_boolean(value));
        } else if (this->elements[i].type == json_type_int) {
            this->elements[i].obj = new int(json_object_get_int(value));
        }

        break;
    }

    if (result == false) {
        bool retval;

        retval = QblJsonObject::parse(key, value);
        if (retval == false) {
            throw QblJsonException("Element \"%s\" is not allowed here\n", key);
        }
    }

    return (result);
}

std::string QblJsonChat::getJsonString()
{
    std::string result;
    int i;
    int elements[] = { SENDER, MESSAGE_TYPE };

    result = "{";
    result += QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++) {
        result += "\"";
        result += this->elements[elements[i]].name;
        result += "\":";
        if (this->elements[elements[i]].type == json_type_string) {
            result += "\"";
            result += *(std::string *) this->elements[elements[i]].obj;
            result += "\"";
        } else if (this->elements[elements[i]].type == json_type_int) {
            result += to_string(*(int *) this->elements[elements[i]].obj);
        }
        result += ",";
    }

    return (result);
}

void QblJsonChat::integrate(QblJson * other)
{
    // TODO: add all elements
    QblJsonObject::integrate(other);

    this->setSender(((QblJsonChat *) other)->getSender());
    this->setMessage(((QblJsonChat *) other)->getMessage());

    return;
}

const std::string & QblJsonChat::getSender() const
{
    return (*((std::string *) this->elements[SENDER].obj));
}

QblJsonChat::messageType QblJsonChat::getType() const
{
    return (*((messageType *) this->elements[MESSAGE_TYPE].obj));
}

const std::string & QblJsonChat::getMessage() const
{
    return (*((std::string *) this->elements[MESSAGE].obj));
}

bool QblJsonChat::isYesNo() const
{
    return (*((bool *) this->elements[YES_NO].obj));
}

const std::string& QblJsonChat::getFile() const
{
    return (*((std::string *) this->elements[FILE].obj));
}

const std::string& QblJsonChat::getFileName() const
{
    return (*((std::string *) this->elements[FILE_NAME].obj));
}

const std::string& QblJsonChat::getServer() const
{
    return (*((std::string *) this->elements[SERVER].obj));
}

int QblJsonChat::getPort() const
{
    return (*((int *) this->elements[PORT].obj));
}

const std::string& QblJsonChat::getPath() const
{
    return (*((std::string *) this->elements[PATH].obj));
}

const std::string& QblJsonChat::getKey() const
{
    return (*((std::string *) this->elements[KEY].obj));
}

const std::string& QblJsonChat::getPublic() const
{
    return (*((std::string *) this->elements[PUBLIC].obj));
}

int QblJsonChat::getUuidToSend() const
{
    return (*((int *) this->elements[UUID_TO_SEND].obj));
}

int64_t QblJsonChat::getMac() const
{
    return (*((int64_t *) this->elements[UUID_TO_SEND].obj));
}

const bool & QblJsonChat::isMessageSend() const
{
    return (*((bool *) this->elements[SEND].obj));
}

void QblJsonChat::setSendState(const bool & state)
{
    this->elements[SEND].obj = new bool(state);

    if (this->getFile().size() > 0) {
        this->setFile("");
    }

    return;
}

void QblJsonChat::setSender(const std::string & sender)
{
    this->elements[SENDER].obj = new std::string(sender);

    return;
}

void QblJsonChat::setType(messageType type)
{
    this->elements[MESSAGE_TYPE].obj = new int(type);
}

void QblJsonChat::setMessage(const std::string & message)
{
    this->elements[MESSAGE].obj = new std::string(message);

    return;
}

void QblJsonChat::setYesNo(bool yesNo)
{
    this->elements[YES_NO].obj = new bool(yesNo);

    return;
}

void QblJsonChat::setKey(const std::string& key)
{
    this->elements[KEY].obj = new std::string(key);

    return;
}

void QblJsonChat::setFile(const std::string& file)
{
    this->elements[FILE].obj = new std::string(file);

    return;
}

void QblJsonChat::setFileName(const std::string& fileName)
{
    this->elements[FILE_NAME].obj = new std::string(fileName);

    return;
}

void QblJsonChat::setServer(const std::string& blockServer)
{
    this->elements[SERVER].obj = new std::string(blockServer);

    return;
}

void QblJsonChat::setPort(int port)
{
    this->elements[PORT].obj = new int(port);

    return;
}

void QblJsonChat::setPath(const std::string& path)
{
    this->elements[PATH].obj = new std::string(path);

    return;
}

void QblJsonChat::setPublic(const std::string& _public)
{
    this->elements[PUBLIC].obj = new std::string(_public);

    return;
}

void QblJsonChat::setUuidToSend(int value)
{
    this->elements[UUID_TO_SEND].obj = new int(value);

    return;
}

void QblJsonChat::setMac()
{
    Qbl *qbl;

    qbl = Qbl::getInstance();
    this->elements[MAC].obj = new int64_t(qbl->getMac()->getFirstMacAddress());

    return;
}
