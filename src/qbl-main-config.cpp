/*
 * @file		qbl-main-config.cpp
 * @brief		Class to handle main configuration (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <iterator>

#include "qbl.h"
#include "qbl-main-config.h"
#include "qbl-json-main-config.h"
#include "qbl-config-file.h"

QblMainConfig::QblMainConfig(const std::string &fileName) :
        fileName(fileName)
{
    std::string str;
    ifstream inputConfigFile;

    inputConfigFile.unsetf(ios_base::skipws);
    inputConfigFile.open(fileName);

    // TODO check for encryption
    if (!inputConfigFile) {
        this->config = new QblJsonMainConfig();
        return;
    } else {
        if (inputConfigFile.bad()) {
            std::string errmsg = "Error when opening config file ";
            std::string errorNumber = std::to_string(errno);
            std::string errorDesc(strerror(errno));
            throw QblException { errmsg, errorNumber, errorDesc };
        }
        std::istream_iterator<char> begin(inputConfigFile), end_of_file;
        str = std::string(begin, end_of_file);
        this->config = new QblJsonMainConfig(str);
        this->bDefault = false;
    }
    inputConfigFile.close();

    return;
}

QblMainConfig::QblMainConfig()
{
    this->config = new QblJsonMainConfig();
    return;
}

QblMainConfig::~QblMainConfig()
{
    return;
}

QblJsonMainConfigAccount *QblMainConfig::getAccounts()
{
    return (this->config->getAccounts());
}

QblJsonMainConfigBlockServerArray *QblMainConfig::getBlockServers()
{
    return (this->config->getBlockServers());
}

QblJsonMainConfigContactArray *QblMainConfig::getContacts()
{
    return (this->config->getContacts());
}

QblJsonMainConfigDropServerArray *QblMainConfig::getDropServers()
{
    return (this->config->getDropServers());
}

QblJsonMainConfigGroupArray *QblMainConfig::getGroups()
{
    return (this->config->getGroups());
}

QblJsonMainConfigIdentityArray *QblMainConfig::getIdentities()
{
    return (this->config->getIdentities());
}

void QblMainConfig::addIdentity(const std::string& alias,
        const std::string& privateKey, const std::string& publicKey,
        const std::string& inbox)
{
    this->config->addIdentity(alias, privateKey, publicKey, inbox);
    this->configIsChanged();
}

QblJsonMainConfigContact * QblMainConfig::addContact(const std::string& alias, const std::string& inbox, const std::string& publicKey, const std::string& myId)
{
    QblJsonMainConfigContact *contact = new QblJsonMainConfigContact();
    contact->setAlias(alias);
    contact->setInbox(inbox);
    contact->setPublicKey(publicKey);
    contact->setMyId(myId);
    this->config->getContacts()->addEntry(contact);
    this->configIsChanged();
    return contact;
}

QblJsonMainConfigPreferences* QblMainConfig::getPreferences()
{
    return (this->config->getPreferences());
}

QblJsonMainConfigShareArray* QblMainConfig::getShares()
{
    return (this->config->getShares());
}

QblJsonMainConfigUploadArray* QblMainConfig::getUploads()
{
    return (this->config->getUploads());
}

QblJsonMainConfigFFSyncUser* QblMainConfig::getFFSyncUser()
{
    return (this->config->getFFSyncUser());
}

void QblMainConfig::configIsChangedBySync(double timestamp)
{
    Qbl::getInstance()->getConfig()->getFFSyncUser()->setModified(timestamp);
    // TODO caching function for changes in config
    if (this->fileName.length() == 0) {
        fileName = QblConfigFile::getConfigFileName();
    }
    this->bDefault = false;
    this->writeConfig();
}

void QblMainConfig::configIsChanged()
{
    // TODO caching function for changes in config
    if (this->fileName.length() == 0) {
        fileName = QblConfigFile::getConfigFileName();
    }
    this->bDefault = false;
    this->writeConfig();
}

bool QblMainConfig::isDefault()
{
    return bDefault;
}

void QblMainConfig::writeConfig()
{
    int file;
    ssize_t length;
    std::string string;

    string = this->config->getJsonString();

    file = open(fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (file == -1) {
        std::string errmsg = "Cannot open config file ";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror(errno));
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    length = write(file, string.data(), string.size());
    if (length != (ssize_t) string.size()) {
        if (length == -1) {
            std::string errmsg = "Cannot open config file ";
            std::string errorNumber = std::to_string(errno);
            std::string errorDesc(strerror(errno));
            throw QblException { errmsg, errorNumber, errorDesc };

        } else {
            throw QblException { "Cannot write all data to config file "
                    + this->fileName };
        }
    }

    // TODO check for encryption
    close(file);
    return;
}
