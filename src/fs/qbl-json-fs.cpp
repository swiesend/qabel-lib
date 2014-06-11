/*
 * @file		qbl-json-fs.cpp
 * @brief		Class to cache file information for reuse (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-fs.h"

QblJsonFs::QblJsonFs() :
        QblJson()
{

    return;
}

QblJsonFs::~QblJsonFs()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
//        TODO free memory
    }

    return;
}

void QblJsonFs::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonFs::parse(json_object *obj)
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
        if (this->elements[i].mandatory == true) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    return;
}

std::string QblJsonFs::getJsonString()
{
    std::string result;
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        result += QblJson::getJsonString(&this->elements[i]);
        result += ",";
    }

    // Remove last comma
    return (result.substr(0, result.size() - 1));
}

void QblJsonFs::integrate(QblJson* other)
{
    this->setName(((QblJsonFs *) other)->getName());
    this->setModDate(((QblJsonFs *) other)->getModDate());

    return;
}

int QblJsonFs::getModDate() const
{
    return (*((int *) this->elements[MOD_DATE].obj));
}

void QblJsonFs::setModDate(int modDate)
{
    this->elements[MOD_DATE].obj = new int(modDate);

    return;
}

const std::string& QblJsonFs::getName() const
{
    return (*((std::string *) this->elements[NAME].obj));
}

void QblJsonFs::setName(const std::string& name)
{
    this->elements[NAME].obj = new std::string(name);

    return;
}
