/*
 * @file		qbl-json-main-config.h
 * @brief		Class to handle the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef QBL_JSON_MAIN_CONFIG_H_
#define QBL_JSON_MAIN_CONFIG_H_

#include "qbl-json.h"
#include "qbl-json-main-config-account-array.h"
#include "qbl-json-main-config-blockserver-array.h"
#include "qbl-json-main-config-contact-array.h"
#include "qbl-json-main-config-dropserver-array.h"
#include "qbl-json-main-config-group-array.h"
#include "qbl-json-main-config-identity-array.h"
#include "qbl-json-main-config-preferences.h"
#include "qbl-json-main-config-share-array.h"
#include "qbl-json-main-config-upload-array.h"
#include "qbl-json-main-config-ffsync-user.h"

/**
 * Class QblJsonMainConfig: Class to handle the main configuration
 */
class QblJsonMainConfig:public QblJson {
  public:
    /**
	 * Enum with the main element which exists in the configuration
	 */
    enum elementType {
        ACCOUNTS = 0,           //!< Accounts
        BLOCK_SERVERS = 1,      //!< Blocked servers
        CONTACTS = 2,           //!< Contacts
        DROP_SERVERS = 3,       //!< Drop servers
        GROUPS = 4,             //!< Groups
        IDENTITIES = 5,         //!< Identities
        PREFERENCES = 6,        //!< Preferences
        SHARES = 7,             //!< Shares
        UPLOADS = 8,            //!< Uploads
        FFSYNC_USER = 9         //!< FFSync User
    };
    /**
     * Constructor
     * @param string Main configuration JSON string
     */
    QblJsonMainConfig(std::string string);
    /**
     * Constructor
     */
    QblJsonMainConfig();
    /**
     * Destructor
     */
    virtual ~ QblJsonMainConfig();

    /**
     * Virtual function to parse the JSON string
     * @param string JSON string to parse
     */
    void parse(std::string string);
    /**
     * Virtual function to parse the JSON object
     * @todo to implement
     * @param obj Object to parse
     */
    void parse(json_object * obj = NULL);
    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    void integrate(QblJson * other);

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
     * @brief addIdentity
     * @param alias Alias of the identity
     * @param privateKey private key of the identity
     * @param publicKey public key of the identity
     * @param inbox inbox of the identity
     */
    void addIdentity(const std::string& alias, const std::string& privateKey, const std::string& publicKey, const std::string& inbox);
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
     * Get ffsync user from main configuration
     * @return  Existing ffsync user
     */
    QblJsonMainConfigFFSyncUser *getFFSyncUser();

  private:
    /**
     * Array which handle all main elements
     */
    struct element elements[10] = {
        {"accounts", json_type_array, new QblJsonMainConfigAccountArray(),
            FALSE, TRUE, TRUE},
        {"block_servers", json_type_array,
            new QblJsonMainConfigBlockServerArray(), FALSE, TRUE, TRUE},
        {"contacts", json_type_array, new QblJsonMainConfigContactArray(),
            FALSE, FALSE, TRUE},
        {"drop_servers", json_type_array,
            new QblJsonMainConfigDropServerArray(), FALSE, TRUE, TRUE},
        {"groups", json_type_array, new QblJsonMainConfigGroupArray(),
            FALSE, FALSE, TRUE},
        {"identities", json_type_array, new QblJsonMainConfigIdentityArray(),
            FALSE, FALSE, TRUE},
        {"preferences", json_type_object, new QblJsonMainConfigPreferences(),
            FALSE, TRUE, TRUE},
        {"shares", json_type_array, new QblJsonMainConfigShareArray(), FALSE,
            TRUE, TRUE},
        {"uploads", json_type_array, new QblJsonMainConfigUploadArray(), FALSE,
            TRUE, TRUE},
        {"ffsync_user", json_type_object, new QblJsonMainConfigFFSyncUser(),
            FALSE, TRUE, TRUE}
    };

};

#endif                          /* QBL_JSON_MAIN_CONFIG_H_ */
