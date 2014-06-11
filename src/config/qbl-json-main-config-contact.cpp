/*
 * @file		qbl-json-main-config-contact.cpp
 * @brief		Class to handle the contacts in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>


#include "qbl-json-object.h"
#include "qbl-json.h"
#include "qbl-json-main-config-contact.h"


QblJsonMainConfigContact::QblJsonMainConfigContact() :
        QblJson()
{

    return;
}

QblJsonMainConfigContact::~QblJsonMainConfigContact()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
    	// TODO free memory?
    }

    return;
}

void QblJsonMainConfigContact::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigContact::parse(json_object *obj)
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
            ((std::string *) this->elements[i].obj)->clear();
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

    this->setInbox(this->getInboxString());

    return;
}

std::string QblJsonMainConfigContact::getJsonString()
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

void QblJsonMainConfigContact::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setAlias(((QblJsonMainConfigContact *)other)->getAlias());
    this->setInbox(((QblJsonMainConfigContact *)other)->getInboxString());
    this->setMyId(((QblJsonMainConfigContact *)other)->getMyId());
    this->setPublicKey(((QblJsonMainConfigContact *)other)->getPublicKey());
    this->setForename(((QblJsonMainConfigContact *) other)->getForename());
    this->setSurname(((QblJsonMainConfigContact *) other)->getSurname());
    this->setMailAddress(((QblJsonMainConfigContact *) other)->getMailAddress());
    this->setPhoneNumber(((QblJsonMainConfigContact *) other)->getPhoneNumber());
    this->setNotes(((QblJsonMainConfigContact *) other)->getNotes());

    return;
}

const std::string& QblJsonMainConfigContact::getAlias() const
{
    return (*((std::string *) this->elements[ALIAS].obj));
}

void QblJsonMainConfigContact::setAlias(const std::string& alias)
{
    if(this->elements[ALIAS].obj != &alias) {
        ((std::string *)this->elements[ALIAS].obj)->clear();
        ((std::string *)this->elements[ALIAS].obj)->append(alias);
    }
    return;
}

const QblConfigInbox& QblJsonMainConfigContact::getInbox() const
{
    return (*this->inbox);
}

const std::string& QblJsonMainConfigContact::getInboxString() const
{
    return (*((std::string *) this->elements[INBOX].obj));
}

void QblJsonMainConfigContact::setInbox(const std::string& inbox)
{
    if(this->elements[INBOX].obj != &inbox) {
        ((std::string *)this->elements[INBOX].obj)->clear();
        ((std::string *)this->elements[INBOX].obj)->append(inbox);
    }
    if(this->inbox != NULL) {
        delete(this->inbox);
    }
    this->inbox = new QblConfigInbox(*((std::string *)this->elements[INBOX].obj));
    return;
}

const std::string& QblJsonMainConfigContact::getMyId() const
{
    return (*((std::string *) this->elements[MY_ID].obj));
}

void QblJsonMainConfigContact::setMyId(const std::string& myId)
{
    if(this->elements[MY_ID].obj != &myId) {
        ((std::string *)this->elements[MY_ID].obj)->clear();
        ((std::string *)this->elements[MY_ID].obj)->append(myId);
    }
    return;
}

const std::string& QblJsonMainConfigContact::getPublicKey() const
{

    return (*((std::string *) this->elements[PUBLIC_KEY].obj));
}

RSA *QblJsonMainConfigContact::getPublicRsaKey() const
{
    const char *key = (*((std::string *) this->elements[PUBLIC_KEY].obj)).c_str();
    BIO *bufio;
    RSA *rsa;
    int byteCount = strlen(key);

    bufio = BIO_new_mem_buf((void*)key, byteCount);
    RSA *myRSA = PEM_read_bio_RSA_PUBKEY(bufio, 0, 0, 0);
    return myRSA;
}

void QblJsonMainConfigContact::setPublicKey(const std::string& publicKey)
{
    if(this->elements[PUBLIC_KEY].obj != &publicKey) {
        ((std::string *)this->elements[PUBLIC_KEY].obj)->clear();
        ((std::string *)this->elements[PUBLIC_KEY].obj)->append(publicKey);
    }
    return;
}

const std::string& QblJsonMainConfigContact::getForename() const
{
    return (*((std::string *) this->elements[FORENAME].obj));
}

void QblJsonMainConfigContact::setForename(const std::string& forename)
{
    if(this->elements[FORENAME].obj != &forename) {
        ((std::string *)this->elements[FORENAME].obj)->clear();
        ((std::string *)this->elements[FORENAME].obj)->append(forename);
    }
    return;
}

const std::string& QblJsonMainConfigContact::getSurname() const
{
    return (*((std::string *) this->elements[SURNAME].obj));
}

void QblJsonMainConfigContact::setSurname(const std::string& surname)
{
    if(this->elements[SURNAME].obj != &surname) {
        ((std::string *)this->elements[SURNAME].obj)->clear();
        ((std::string *)this->elements[SURNAME].obj)->append(surname);
    }    
    return;
}

const std::string& QblJsonMainConfigContact::getMailAddress() const
{
    return (*((std::string *) this->elements[MAIL].obj));
}

void QblJsonMainConfigContact::setMailAddress(const std::string& mailAddress)
{
    if(this->elements[MAIL].obj != &mailAddress) {
        ((std::string *)this->elements[MAIL].obj)->clear();
        ((std::string *)this->elements[MAIL].obj)->append(mailAddress);
    }
    
    return;
}

const std::string& QblJsonMainConfigContact::getPhoneNumber() const
{
    return (*((std::string *) this->elements[PHONE].obj));
}

void QblJsonMainConfigContact::setPhoneNumber(const std::string& phoneNumber)
{
    if(this->elements[PHONE].obj != &phoneNumber) {
        ((std::string *)this->elements[PHONE].obj)->clear();
        ((std::string *)this->elements[PHONE].obj)->append(phoneNumber);
    }    
    return;
}

const std::string& QblJsonMainConfigContact::getNotes() const
{
    return (*((std::string *) this->elements[NOTES].obj));
}

void QblJsonMainConfigContact::setNotes(const std::string& notes)
{
    if(this->elements[NOTES].obj != &notes) {
        ((std::string *)this->elements[NOTES].obj)->clear();
        ((std::string *)this->elements[NOTES].obj)->append(notes);
    }
    return;
}

const std::string& QblJsonMainConfigContact::getKey() const
{
    return (*((std::string *) this->elements[PUBLIC_KEY].obj));
}

