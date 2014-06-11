/*
 * @file		qbl-json-main-config-identity.cpp
 * @brief		Class to handle the identities in the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-json-main-config-identity.h"

#include <json_object.h>
#include <linkhash.h>
#include <string.h>
#include <cstdio>
#include <ctime>

#include "qbl-json-object.h"

QblJsonMainConfigIdentity::QblJsonMainConfigIdentity() :
        QblJson()
{
	time_t start;
    int buffer_length = 30;
    char buffer[buffer_length];
    struct tm tm;

    memset(&tm, '\0', sizeof(struct tm));
	start = mktime(&tm);
	strftime(buffer, buffer_length, "%a, %d %b %Y %T %Z", localtime(&start));

	this->elements[LAST_UPDATE].obj = new std::string(buffer);

    return;
}

QblJsonMainConfigIdentity::~QblJsonMainConfigIdentity()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
    }

    return;
}

void QblJsonMainConfigIdentity::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigIdentity::parse(json_object *obj)
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
            ((std::string *)this->elements[i].obj)->clear();
            ((std::string *)this->elements[i].obj)->append(json_object_get_string(value));

            
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
        if (this->elements[i].mandatory == true
                && this->elements[i].checked == false) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    this->setInbox(this->getInboxString());

    return;
}

std::string QblJsonMainConfigIdentity::getJsonString()
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

void QblJsonMainConfigIdentity::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setAlias(((QblJsonMainConfigIdentity *)other)->getAlias());
    this->setInbox(((QblJsonMainConfigIdentity *)other)->getInboxString());
    this->setPrivateKey(((QblJsonMainConfigIdentity *)other)->getPrivateKey());
    this->setPublicKey(((QblJsonMainConfigIdentity *)other)->getPublicKey());

    return;
}

const std::string& QblJsonMainConfigIdentity::getAlias() const
{
    return (*((std::string *) this->elements[ALIAS].obj));
}

void QblJsonMainConfigIdentity::setAlias(const std::string& alias)
{
    if(this->elements[ALIAS].obj != &alias) {
        ((std::string *)this->elements[ALIAS].obj)->clear();
        ((std::string *)this->elements[ALIAS].obj)->append(alias);
    }

    return;
}

const QblConfigInbox& QblJsonMainConfigIdentity::getInbox() const
{
    return (*this->inbox);
}

const std::string& QblJsonMainConfigIdentity::getInboxString() const
{
    return (*((std::string *) this->elements[INBOX].obj));
}

void QblJsonMainConfigIdentity::setInbox(const std::string& inbox)
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

const std::string& QblJsonMainConfigIdentity::getPrivateKey() const
{
    return (*((std::string *) this->elements[PRIVATE_KEY].obj));
}

RSA* QblJsonMainConfigIdentity::getPrivateRsaKey() const
{
    const char *key = (*((std::string *) this->elements[PUBLIC_KEY].obj)).c_str();
    BIO *bufio;
    RSA *rsa;
    int byteCount = strlen(key);

    bufio = BIO_new_mem_buf((void*)key, byteCount);
    RSA *myRSA = PEM_read_bio_RSA_PUBKEY(bufio, 0, 0, 0);
    return myRSA;
}

void QblJsonMainConfigIdentity::setPrivateKey(const std::string& privateKey)
{
    if(this->elements[PRIVATE_KEY].obj != &privateKey) {
        ((std::string *)this->elements[PRIVATE_KEY].obj)->clear();
        ((std::string *)this->elements[PRIVATE_KEY].obj)->append(privateKey);
    }

    return;
}

const std::string& QblJsonMainConfigIdentity::getPublicKey() const
{
    return (*((std::string *) this->elements[PUBLIC_KEY].obj));
}

void QblJsonMainConfigIdentity::setPublicKey(const std::string& publicKey)
{
    if(this->elements[PUBLIC_KEY].obj != &publicKey) {
        ((std::string *)this->elements[PUBLIC_KEY].obj)->clear();
        ((std::string *)this->elements[PUBLIC_KEY].obj)->append(publicKey);
    }

    return;
}

const std::string& QblJsonMainConfigIdentity::getLastUpdate() const
{
    return (*((std::string *) this->elements[LAST_UPDATE].obj));
}

void QblJsonMainConfigIdentity::setLastUpdate(const std::string& lastUpdate)
{
    if(this->elements[LAST_UPDATE].obj != &lastUpdate) {
        ((std::string *)this->elements[LAST_UPDATE].obj)->clear();
        ((std::string *)this->elements[LAST_UPDATE].obj)->append(lastUpdate);
    }
    return;
}
