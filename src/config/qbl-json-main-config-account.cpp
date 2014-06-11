/*
 * @file		qbl-json-main-config-account.cpp
 * @brief		Class to handle the accounts in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>

#include "qbl-json-object.h"
#include "qbl-json.h"
#include "qbl-json-main-config-account.h"

QblJsonMainConfigAccount::QblJsonMainConfigAccount() : QblJson()
{

    return;
}

QblJsonMainConfigAccount::~QblJsonMainConfigAccount()
{

    return;
}

void QblJsonMainConfigAccount::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigAccount::parse(json_object *obj)
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

std::string QblJsonMainConfigAccount::getJsonString()
{
    std::string result;
    int i;

    result = QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        result += "\"";
        result += this->elements[i].name;
        result += "\":\"";
        result += *(std::string *) this->elements[i].obj;
        result += "\",";
    }

    // Remove last comma
    return (result.substr(0, result.size() - 1));
}

void QblJsonMainConfigAccount::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setProvider(((QblJsonMainConfigAccount *)other)->getProvider());
    this->setUser(((QblJsonMainConfigAccount *)other)->getUser());
    this->setAuth(((QblJsonMainConfigAccount *)other)->getAuth());
    return;
}

const std::string& QblJsonMainConfigAccount::getProvider() const{
    return (*((std::string *) this->elements[PROVIDER].obj));
}

void QblJsonMainConfigAccount::setProvider(const std::string& provider) {
    if(this->elements[PROVIDER].obj != &provider) {
        ((std::string *)this->elements[PROVIDER].obj)->clear();
        ((std::string *)this->elements[PROVIDER].obj)->append(provider);
    }
    return;
}

const std::string& QblJsonMainConfigAccount::getUser() const {
    return (*((std::string *) this->elements[USER].obj));
}

void QblJsonMainConfigAccount::setUser(const std::string& user) {
    if(this->elements[USER].obj != &user) {
        ((std::string *)this->elements[USER].obj)->clear();
        ((std::string *)this->elements[USER].obj)->append(user);
    }
    return;
}

const std::string& QblJsonMainConfigAccount::getAuth() const {
    return (*((std::string *) this->elements[AUTH].obj));
}

void QblJsonMainConfigAccount::setAuth(const std::string& auth) {
    if(this->elements[AUTH].obj != &auth) {
        ((std::string *)this->elements[AUTH].obj)->clear();
        ((std::string *)this->elements[AUTH].obj)->append(auth);
    }
    return;
}
