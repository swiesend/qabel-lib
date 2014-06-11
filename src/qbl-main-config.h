/*
 * @file		qbl-main-config.h
 * @brief		Class to handle main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_MAIN_CONFIG_H__
#define __QBL_MAIN_CONFIG_H__

#include <stdarg.h>

#include "qbl-json.h"
#include "qbl-json-main-config.h"

#define BUFFER_LENGTH 1024

class QblMainConfig {
public:
    QblMainConfig(const std::string &fileName);
    QblMainConfig();
    virtual ~QblMainConfig();

    /**
     * Get accounts from main configuration
     * @return Existing accounts
     */
    QblJsonMainConfigAccount *getAccounts();
    /**
     * Get blocked servers from main configuration
     * @return Existing blocked servers
     */
    QblJsonMainConfigBlockServerArray *getBlockServers();
    /**
     * Get contacts from main configuration
     * @return Existing contacts
     */
    QblJsonMainConfigContactArray *getContacts();
    /**
     * Get drop servers from main configuration
     * @return Existing drop servers
     */
    QblJsonMainConfigDropServerArray *getDropServers();
    /**
     * Get groups from main configuration
     * @return Existing groups
     */
    QblJsonMainConfigGroupArray *getGroups();
    /**
     * Get identities from main configuration
     * @return Existing identities
     */
    QblJsonMainConfigIdentityArray *getIdentities();
    /**
     * Add an identity to the main configuration
     * @param alias Alias of the identity
     * @param privateKey private key of the identity
     * @param publicKey public key of the identity
     * @param inbox inbox of the identity
     */
    void addIdentity(const std::string& alias,const std::string& privateKey,const std::string& publicKey,const std::string& inbox);
    /**
     * 
     * @brief addContact
     * @param alias
     * @param inbox
     * @param publicKey
     */
    QblJsonMainConfigContact *addContact(const std::string& alias, const std::string& inbox, const std::string& publicKey, const std::string& myId);
    
    /**
     * Get preferences from main configuration
     * @return Existing preferences
     */
    QblJsonMainConfigPreferences *getPreferences();
    /**
     * Get shares from main configuration
     * @return Existing shares
     */
    QblJsonMainConfigShareArray *getShares();
    /**
     * Get uploads from main configuration
     * @return Existing uploads
     */
    QblJsonMainConfigUploadArray *getUploads();
    /**
     * Get FFSync User from main config
     * @return Existing FFSync User
     */
    QblJsonMainConfigFFSyncUser *getFFSyncUser();
    /**
     * @brief This function have to called when the main configuration is changed by FFSync
     * @param timestamp
     */
    void configIsChangedBySync(double timestamp);

    /**
     * This function have to called when the main configuration is changed
     */
    void configIsChanged();
    bool isDefault();

private:
	std::string fileName; /**< Name of the config file */
    QblJsonMainConfig *config; /**< Parsed configuration */
    bool bDefault = true;
    /**
     * Write configuration back to disk
     */
    void writeConfig();
};

#endif /* __QBL_MAIN_CONFIG_H__ */
