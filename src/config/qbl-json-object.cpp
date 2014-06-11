/*
 * @file		qbl-json-object.cpp
 * @brief		Main Class for the JSON stuff (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdlib.h>
#include <json_tokener.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "qbl.h"
#include "qbl-json-object.h"

#define BUFFER_LENGTH 1024

QblJsonObject::QblJsonObject() :
        obj(NULL), created(time(NULL)), updated(time(NULL)), deleted(0)
{
    this->createUuid();

    return;
}

QblJsonObject::~QblJsonObject()
{

    return;
}

int64_t QblJsonObject::getUuid() const
{
    return (this->uuid);
}

time_t QblJsonObject::getCreated() const
{
    return (this->created);
}

time_t QblJsonObject::getUpdated() const
{
    return (this->updated);
}

time_t QblJsonObject::getDeleted() const
{
    return (this->deleted);
}

uint8_t QblJsonObject::compare(QblJsonObject* other)
{
    uint8_t result = 0;

    if (this->getUuid() == other->getUuid()) {
        result = result | EQUAL_UUID;
        if (this->getUpdated() == other->getUpdated()) {
            result = result | EQUAL_DATE;
        } else if (this->getUpdated() < other->getUpdated()) {
            result = result | DATE_NEWER;
        }
    }

    return (result);
}

bool QblJsonObject::isUuidEqual(uint8_t compareResult)
{
    return ((compareResult & EQUAL_UUID) ? true : false);
}

bool QblJsonObject::isDateEqual(uint8_t compareResult)
{
    if (QblJsonObject::isUuidEqual(compareResult) == true) {
        return ((compareResult & EQUAL_DATE) ? true : false);
    }

    return (false);
}

bool QblJsonObject::isDateNewer(uint8_t compareResult)
{
    if (QblJsonObject::isDateEqual(compareResult) == false) {
        return ((compareResult & DATE_NEWER) ? true : false);
    }

    return (false);
}

bool QblJsonObject::parse(const char* key, json_object* value)
{
    if (!strcmp(key, "uuid")) {
        this->setUuid(json_object_get_int64(value));
        return (true);
    } else if (!strcmp(key, "created")) {
        this->setCreated(json_object_get_int64(value));
        return (true);
    } else if (!strcmp(key, "updated")) {
        this->setUpdated(json_object_get_int64(value));
        return (true);
    } else if (!strcmp(key, "deleted")) {
        this->setDeleted(json_object_get_int64(value));
        return (true);
    }

    return (false);
}

void QblJsonObject::integrate(QblJsonObject* other)
{
    this->setCreated(other->getCreated());
    this->setUpdated(other->getUpdated());
    this->setDeleted(other->getDeleted());
}

bool QblJsonObject::addStringList(json_object * /*obj*/,
        std::list<std::string> /*list*/)
{
    return (true);
}

std::list<std::string> QblJsonObject::getStringList(json_object *obj)
        throw (QblJsonException&)
{
    std::list<std::string> result;
    int i, length;
    json_object *value;
    std::string buffer;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        value = json_object_array_get_idx(obj, i);
        buffer = json_object_get_string(value);
        if (errno) {
            throw QblJsonException{
                    "Cannot get string value for JSON object \"%s\": %s (%d)\n",
                    strerror(errno), errno};
        }
        result.push_back(buffer);
    }

    return (result);
}

bool QblJsonObject::addIntList(json_object * /*obj*/, std::list<int> /*list*/)
{

    return (true);
}

std::list<int> QblJsonObject::getIntList(json_object *obj)
        throw (QblJsonException&)
{
    std::list<int> result;
    int i, length;
    json_object *value;
    int buffer;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        value = json_object_array_get_idx(obj, i);
        buffer = json_object_get_int(value);
        if (errno) {
            throw QblJsonException(
                    "Cannot get int value for JSON object \"%s\": %s (%d)\n",
                    strerror(errno), errno);
        }
        result.push_back(buffer);
    }

    return (result);
}

bool QblJsonObject::addDoubleList(json_object * /*obj*/, std::list<double> /*list*/)
{

    return (true);
}

std::list<double> QblJsonObject::getDoubleList(json_object *obj)
        throw (QblJsonException&)
{
    std::list<double> result;
    int i, length;
    json_object *value;
    double buffer;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        value = json_object_array_get_idx(obj, i);
        buffer = json_object_get_double(value);
        if (errno) {
            throw QblJsonException(
                    "Cannot get double value for JSON object \"%s\": %s (%d)\n",
                    strerror(errno), errno);
        }
        result.push_back(buffer);
    }

    return (result);
}

void QblJsonObject::createUuid()
{
    this->uuid = (int64_t)random();

    return;
}

void QblJsonObject::setUuid(int64_t uuid)
{
    this->uuid = uuid;

    return;
}

void QblJsonObject::setCreated(time_t timestamp)
{
    this->created = timestamp;

    return;
}

int QblJsonObject::setCreated(const char* timestamp)
{
    struct tm tm;

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    if (Qbl::strptime(timestamp, "%Y-%m-%d %T", &tm) == NULL)
#else
    if (strptime(timestamp, "%Y-%m-%d %T", &tm))
#endif
    {
        return (-1);
    }
    this->created = mktime(&tm);
    if (this->created == -1) {
        return (-1);
    }

    return (0);
}

void QblJsonObject::setUpdated(time_t timestamp)
{
    this->updated = timestamp;

    return;
}

int QblJsonObject::setUpdated(const char* timestamp)
{
    struct tm tm;

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    if (Qbl::strptime(timestamp, "%Y-%m-%d %T", &tm) == NULL)
#else
    if (strptime(timestamp, "%Y-%m-%d %T", &tm))
#endif
    {
        return (-1);
    }
    this->updated = mktime(&tm);
    if (this->updated == -1) {
        return (-1);
    }

    return (0);
}

void QblJsonObject::setDeleted(time_t timestamp)
{
    this->deleted = timestamp;

    return;
}

int QblJsonObject::setDeleted(const char* timestamp)
{
    struct tm tm;

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    if (Qbl::strptime(timestamp, "%Y-%m-%d %T", &tm) == NULL)
#else
    if (strptime(timestamp, "%Y-%m-%d %T", &tm))
#endif
    {
        return (-1);
    }
    this->deleted = mktime(&tm);
    if (this->deleted == -1) {
        return (-1);
    }

    return (0);
}
