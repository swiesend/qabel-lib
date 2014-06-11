/*
 * @file		qbl-json-main-config-contact.cpp
 * @brief		Class to handle the contacts in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>

#include "qbl-json-main-config-contact-array.h"

QblJsonMainConfigContactArray::QblJsonMainConfigContactArray() :
        QblJsonArray()
{

    return;
}

QblJsonMainConfigContactArray::~QblJsonMainConfigContactArray()
{
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
    	// TODO free memory?
    }

    return;
}

void QblJsonMainConfigContactArray::parse(std::string string)
{
    QblJson::parse(string);

    this->parse(this->obj);

    return;
}

void QblJsonMainConfigContactArray::parse(json_object *obj)
{
    int i, length;
    json_object *value;

    length = json_object_array_length(obj);
    for (i = 0; i < length; i++) {
        QblJsonMainConfigContact *contact;

        value = json_object_array_get_idx(obj, i);
        contact = new QblJsonMainConfigContact();
        contact->parse(value);
        this->list.push_back((QblJsonObject *) contact);
    }

    return;
}

std::string QblJsonMainConfigContactArray::getJsonString()
{
    std::string result;
    std::list<QblJsonObject *>::iterator iterator;

    result = "\"contacts\":[";

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result += "{";
        result += ((QblJsonMainConfigContact *) (*iterator))->getJsonString();
        result += "},";
    }

    // Remove last comma
    if(this->list.size() > 0) {
        result = result.substr(0, result.size() - 1);
    }
    result += "]";

    return (result);
}

void QblJsonMainConfigContactArray::integrate(QblJson* /*other*/)
{

    return;
}

std::list<QblJsonMainConfigContact *> QblJsonMainConfigContactArray::getList()
{
    std::list<QblJsonMainConfigContact *> result;
    std::list<QblJsonObject *>::iterator iterator;

    for (iterator = this->list.begin(); iterator != this->list.end();
            iterator++) {
        result.push_back((QblJsonMainConfigContact*) *iterator);
    }

    return (result);
}

QblJsonMainConfigContact *QblJsonMainConfigContactArray::getContact(int uuid)
{
    QblJsonMainConfigContact *contact = NULL;
    std::list<QblJsonMainConfigContact *>::iterator iterator;
    std::list<QblJsonMainConfigContact *> contactList = this->getList();

    for (iterator = contactList.begin(); iterator != contactList.end();
            iterator++) {
        if(uuid == (*iterator)->getUuid()) {
            contact = *iterator;
            break;
        }
    }
    
    return contact;
}
