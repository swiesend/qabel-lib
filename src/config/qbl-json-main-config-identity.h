/*
 * @file		qbl-json-main-config-identity.h
 * @brief		Class to handle the identities in the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_IDENTITY_H__
#define __QBL_JSON_MAIN_CONFIG_IDENTITY_H__

#include <string>
#include <openssl/pem.h>
#include <openssl/bio.h>
using namespace std;

#include "qbl-json.h"
#include "qbl-config-inbox.h"

/**
 *
 * class QblJsonMainConfigIdentity: Class to handle the identities in the main
 * configuration (Header file)
 */
class QblJsonMainConfigIdentity: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigIdentity();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigIdentity();

    /**
     * Function to parse the JSON string
     * @return true == everything okay
     */
    void parse(std::string string);
    /**
     * Function to parse the JSON object
     * @param obj Object to parse
     * @return
     */
    void parse(json_object *obj = NULL);
    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    void integrate(QblJson *other);

    /**
     * Get current alias
     * @return Current alias
     */
    const std::string& getAlias() const;
    /**
     * Set new alias
     * @todo not tested
     * @param alias New alias
     */
    void setAlias(const std::string& alias);
    /**
     * Get current inbox
     * @return Current inbox
     */
    const QblConfigInbox& getInbox() const;
    /**
     * Get current inbox
     * @return Current inbox as string
     */
    const std::string& getInboxString() const;
    /**
     * Set new inbox
     * @todo not tested
     * @param inbox New inbox
     */
    void setInbox(const std::string& inbox);
    /**
     * Get current private key
     * @return Current private key
     */
    const std::string& getPrivateKey() const;
    /**
     * Get current private RSA key
     * @return Current private RSA key
     */
    RSA* getPrivateRsaKey() const;
    /**
     * Set new private key
     * @todo not tested
     * @param privateKey New private key
     */
    void setPrivateKey(const std::string& privateKey);
    /**
     * Get current public key
     * @return Current public key
     */
    const std::string& getPublicKey() const;
    /**
     * Set new public key
     * @todo not tested
     * @param publicKey New public key
     */
    void setPublicKey(const std::string& publicKey);
    /**
     * Get last update time stamp
     * @return Last update time stamp
     */
    const std::string& getLastUpdate() const;
    /**
     * Set new last update time stamp
     * @todo not tested
     * @param lastUpdate Last update time stamp
     */
    void setLastUpdate(const std::string& lastUpdate);

private:
    enum elementType {
        ALIAS = 0,
        INBOX = 1,
        PRIVATE_KEY = 2,
        PUBLIC_KEY = 3,
        LAST_UPDATE = 4,
    };
    struct element elements[5] = {
        /** Alias of the identity */
        { "alias", json_type_string, new std::string(), false, true, true },
        /** Inbox of the identity */
        { "inbox", json_type_string, new std::string(), false, true, true },
        /** Private key of the identity */
        { "private_key", json_type_string, new std::string(), false, true,
            true },
        /** Public key of the identity */
        { "public_key", json_type_string, new std::string(), false, true,
            true },
        /** When was the last connection to the inbox */
        { "last_update", json_type_string, new std::string(), false, false,
            false },
    };
    QblConfigInbox *inbox = NULL;           /**< Inbox object */

};

#endif /* __QBL_JSON_MAIN_CONFIG_IDENTITY_H__ */
