/*
 * @file		qbl-json-main-config.cpp
 * @brief		Class to handle the main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <string.h>

#include "qbl-json.h"
#include "qbl-json-main-config.h"

QblJsonMainConfig::QblJsonMainConfig(std::string string) :
        QblJson()
{
    this->parse(string);

    return;
}

QblJsonMainConfig::QblJsonMainConfig() :
        QblJson()
{

    return;
}

QblJsonMainConfig::~QblJsonMainConfig()
{
    int i;

    for (i = 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++) {
        if (elements[i].obj != NULL) {
            if (elements[i].type == json_type_object) {
                delete ((QblJson *) elements[i].obj);
            } else if (elements[i].type == json_type_array) {
                // TODO change when JsonArray is finished
                delete ((QblJson *) elements[i].obj);
            }
        }
    }

    return;
}

void QblJsonMainConfig::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfig::parse(json_object* obj)
{
    int i;

    if (obj != NULL) {
        this->obj = obj;
    }

    json_object_object_foreach(this->obj, key, value) {
        for (i = 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++) {
            if (strcmp(elements[i].name, key)) {
                continue;
            }

            if (elements[i].checked == true) {
                throw QblJsonException("Element \"%s\" already exists\n", key);
            }
            // TODO delete: only for testing
            if (elements[i].obj == NULL) {
                elements[i].checked = true;
                break;
            }
            if (elements[i].type != json_object_get_type(value)) {
                throw QblJsonException("Element \"%s\" have wrong type\n", key);
            }
            ((QblJson *) elements[i].obj)->parse(value);
            elements[i].checked = true;

            break;
        }
    }

    /**
     * Check whether everything is set
     */
    for (i = 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++) {
        if (this->elements[i].mandatory == true
                && this->elements[i].checked == false) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    elements[i].name);
        }
    }

    return;
}

std::string QblJsonMainConfig::getJsonString()
{
    std::string result;
    unsigned int i;
    std::string tmpResult;
    result += "{";
    for (i = 0; i < (sizeof(this->elements)/sizeof(this->elements[0])); i++) {
        tmpResult = ((QblJson*)this->elements[i].obj)->getJsonString();
        if ((this->elements[i].type) == json_type_object) {
            result += "\"";
            result += this->elements[i].name;
            result += "\":";
            result += "{";
        }
        
        result += "\n\t";
        result += tmpResult;
        if (this->elements[i].type == json_type_object) {
            result += "}";
        }
        result += ",";
        
    }

    // remove last comma
    result = result.substr(0, result.size() - 1);
    result += "\n}";
    return (result);
}

void QblJsonMainConfig::integrate(QblJson* /*other*/)
{
    return;
}

QblJsonMainConfigAccount *QblJsonMainConfig::getAccounts()
{
    return ((QblJsonMainConfigAccount*) this->elements[ACCOUNTS].obj);
}

QblJsonMainConfigBlockServerArray *QblJsonMainConfig::getBlockServers()
{
    return ((QblJsonMainConfigBlockServerArray*) this->elements[BLOCK_SERVERS].obj);
}

QblJsonMainConfigContactArray* QblJsonMainConfig::getContacts()
{
    return ((QblJsonMainConfigContactArray*) this->elements[CONTACTS].obj);
}

QblJsonMainConfigDropServerArray *QblJsonMainConfig::getDropServers()
{
    return ((QblJsonMainConfigDropServerArray*) this->elements[DROP_SERVERS].obj);
}

QblJsonMainConfigGroupArray *QblJsonMainConfig::getGroups()
{
    return ((QblJsonMainConfigGroupArray*) this->elements[GROUPS].obj);
}

QblJsonMainConfigIdentityArray *QblJsonMainConfig::getIdentities()
{
    return ((QblJsonMainConfigIdentityArray*) this->elements[IDENTITIES].obj);
}

void QblJsonMainConfig::addIdentity(const std::string& alias, const std::string& privateKey, const std::string& publicKey, const std::string& inbox)
{
       ((QblJsonMainConfigIdentityArray*)this->elements[IDENTITIES].obj)->addIdentity(alias, privateKey, publicKey, inbox);
}

QblJsonMainConfigPreferences *QblJsonMainConfig::getPreferences()
{
    return ((QblJsonMainConfigPreferences*) this->elements[PREFERENCES].obj);
}

QblJsonMainConfigShareArray *QblJsonMainConfig::getShares()
{
    return ((QblJsonMainConfigShareArray*) this->elements[SHARES].obj);
}

QblJsonMainConfigUploadArray *QblJsonMainConfig::getUploads()
{
    return ((QblJsonMainConfigUploadArray*) this->elements[UPLOADS].obj);
}

QblJsonMainConfigFFSyncUser *QblJsonMainConfig::getFFSyncUser()
{
    return ((QblJsonMainConfigFFSyncUser*) this->elements[FFSYNC_USER].obj);
}
