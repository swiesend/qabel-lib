/*
 * @file		qbl-json-main-config-identity.cpp
 * @brief		Class to handle the identities in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-identity-array.h"

QblJsonMainConfigIdentityArray::QblJsonMainConfigIdentityArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigIdentityArray::~QblJsonMainConfigIdentityArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory
    }

    return;
}

void QblJsonMainConfigIdentityArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigIdentityArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigIdentity *identity;

        value = json_object_array_get_idx(obj, i);
        identity = new QblJsonMainConfigIdentity();
        identity->parse(value);
        this->list.push_back((QblJsonObject *) identity);
    }

    return;
}

std::string QblJsonMainConfigIdentityArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"identities\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigIdentity *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigIdentityArray::addIdentity(const std::string& alias,const std::string& privateKey,const std::string& publicKey,const std::string& inbox) {
    QblJsonMainConfigIdentity *identity = new QblJsonMainConfigIdentity();
    identity->setAlias(alias);
    identity->setPrivateKey(privateKey);
    identity->setPublicKey(publicKey);
    identity->setInbox(inbox);
    this->addEntry(identity);
}

void QblJsonMainConfigIdentityArray::integrate(QblJson* /*other*/)
{
    return;
}

std::list<QblJsonMainConfigIdentity *> QblJsonMainConfigIdentityArray::getList()
{
    std::list<QblJsonMainConfigIdentity *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigIdentity*) *iterator);
    }

    return (result);
}
