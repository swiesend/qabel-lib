/*
 * @file		qbl-json-main-config-contact.h
 * @brief		Class to handle the contacts in the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_CONTACT_H__
#define __QBL_JSON_MAIN_CONFIG_CONTACT_H__

#include <json_object.h>
#include <string>
#include <openssl/bio.h>
#include <openssl/pem.h>
using namespace std;

#include "qbl-json-object.h"
#include "qbl-json.h"
#include "qbl-config-inbox.h"

/**
 *
 * class QblJsonMainConfigContact: Class to handle the contacts in the main
 * configuration (Header file)
 */
class QblJsonMainConfigContact: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigContact();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigContact();

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
    const std::string& getMyId() const;
    /**
     * Set new private key
     * @todo not tested
     * @param myId New private key
     */
    void setMyId(const std::string& myId);
    /**
     * Get current public key
     * @return Current public key
     */
    const std::string& getPublicKey() const;
    /**
     * Get current RSA public key
     * @return Current RSA public key
     */
    RSA *getPublicRsaKey() const;
    /**
     * Set new public key
     * @todo not tested
     * @param publicKey New public key
     */
    void setPublicKey(const std::string& publicKey);
    /**
     * Get current forename
     * @return Current forename
     */
    const std::string& getForename() const;
    /**
     * Set new forename
     * @todo not tested
     * @param forename New forename
     */
    void setForename(const std::string& forename);
    /**
     * Get current surname
     * @return Current surname
     */
    const std::string& getSurname() const;
    /**
     * Set new surname
     * @todo not tested
     * @param surname New surname
     */
    void setSurname(const std::string& surname);
    /**
     * Get current mail address
     * @return Current mail address
     */
    const std::string& getMailAddress() const;
    /**
     * Set new mail address
     * @todo not tested
     * @param mailAddress
     */
    void setMailAddress(const std::string& mailAddress);
    /**
     * Get current phone number
     * @return Current phone number
     */
    const std::string& getPhoneNumber() const;
    /**
     * Set new phone number
     * @todo not tested
     * @param phoneNumber
     */
    void setPhoneNumber(const std::string& phoneNumber);
    /**
     * Get current notes
     * @return Current notes
     */
    const std::string& getNotes() const;
    /**
     * Set new notes
     * @todo not tested
     * @param notes
     */
    void setNotes(const std::string& notes);

    const std::string& getKey() const;


private:
    enum elementType {
        ALIAS = 0,
        INBOX = 1,
        MY_ID = 2,
        PUBLIC_KEY = 3,
        FORENAME = 4,
        SURNAME = 5,
        MAIL = 6,
        PHONE = 7,
        NOTES = 8,
    };
    struct element elements[9] = {
        /** Alias of the contact */
        { "alias", json_type_string, new std::string(), false, true, true },
        /** Inbox of the contact */
        { "inbox", json_type_string, new std::string(), false, true, true },
        /** Private key of the contact */
        { "my_id", json_type_string, new std::string(), false, true, true },
        /** Public key of the contact */
        { "public_key", json_type_string, new std::string(), false, true,
            true },
        /** Forename of the contact */
        { "forename", json_type_string, new std::string(), false, true, true },
        /** Surename of the contact */
        { "surname", json_type_string, new std::string(), false, true, true },
        /** Mail address of the contact */
        { "mail", json_type_string, new std::string(), false, true, true },
        /** Phone number of the contact */
        { "phone", json_type_string, new std::string(), false, true, true },
        /** Notes of the contact */
        { "notes", json_type_string, new std::string(), false, true, true },
    };
    QblConfigInbox *inbox = NULL;           /**< Inbox object */

};

#endif /* __QBL_JSON_MAIN_CONFIG_CONTACT_H__ */
