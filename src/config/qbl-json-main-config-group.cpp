/*
 * @file		qbl-json-main-config-group.cpp
 * @brief		Class to handle a group in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config-group.h"

QblJsonMainConfigGroup::QblJsonMainConfigGroup() :
        QblJson()
{

    return;
}

QblJsonMainConfigGroup::~QblJsonMainConfigGroup()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
//        TODO free memory
    }

    return;
}

void QblJsonMainConfigGroup::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigGroup::parse(json_object *obj)
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

std::string QblJsonMainConfigGroup::getJsonString()
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

void QblJsonMainConfigGroup::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setAlias(((QblJsonMainConfigGroup *)other)->getAlias());
    this->setPsKey(((QblJsonMainConfigGroup *)other)->getPsKey());
    this->setInbox(((QblJsonMainConfigGroup *)other)->getInbox());
    return;
}

const std::string& QblJsonMainConfigGroup::getAlias() const{
    return (*((std::string *) this->elements[ALIAS].obj));
}

void QblJsonMainConfigGroup::setAlias(const std::string& alias) {
    if(this->elements[ALIAS].obj != &alias) {
        ((std::string *)this->elements[ALIAS].obj)->clear();
        ((std::string *)this->elements[ALIAS].obj)->append(alias);
    }
    return;
}

const std::string& QblJsonMainConfigGroup::getPsKey() const{
    return (*((std::string *) this->elements[PS_KEY].obj));
}

void QblJsonMainConfigGroup::setPsKey(const std::string& psKey) {
    if(this->elements[PS_KEY].obj != &psKey) {
        ((std::string *)this->elements[PS_KEY].obj)->clear();
        ((std::string *)this->elements[PS_KEY].obj)->append(psKey);
    }
    return;
}

const std::string& QblJsonMainConfigGroup::getInbox() const{
    return (*((std::string *) this->elements[INBOX].obj));
}

void QblJsonMainConfigGroup::setInbox(const std::string& inbox) {
    if(this->elements[INBOX].obj != &inbox) {
        ((std::string *)this->elements[INBOX].obj)->clear();
        ((std::string *)this->elements[INBOX].obj)->append(inbox);
    }
    return;
}
