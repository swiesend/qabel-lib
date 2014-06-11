/*
 * @file		qbl-json-main-config-ffsync-user.h
 * @brief		Class to handle the firefox sync user in the main configuration (Header file)
 * @author		Malte Zobel <zobel@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_FFSYNC_USER_H__
#define __QBL_JSON_MAIN_CONFIG_FFSYNC_USER_H__

#include <string>
#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigUFFSync: Class to handle the firefox sync user in the main
 * configuration (Header file)
 */
class QblJsonMainConfigFFSyncUser: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigFFSyncUser();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigFFSyncUser();

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
     * Get current username
     * @return Current value
     */
    const std::string& getUsername() const;

    /**
     * Set new username
     * @param new value
     */
    void setUsername(const std::string& value);

    /**
     * Get current mail adress
     * @return Current Value
     */
    const std::string& getMail() const;

    /**
     * Set new mail adress
     * @param value
     */
    void setMail(const std::string& value);

    /**
     * Get the current password
     * @return Current value
     */
    const std::string& getPassword() const;

    /**
     * Set new password
     * @param value
     */
    void setPassword(const std::string& value);

    /**
     * Get the current url
     * @return Current Value
     */
    const std::string& getUrl() const;

    /**
     * Set new url
     * @param value
     */
    void setUrl(const std::string& value);

    /**
     * Get current node
     * @return Current value
     */
    int getPort() const;

    /**
     * Set new node
     * @param value
     */
    void setPort(const int value);
    
    /**
     * Get current node
     * @return Current value
     */
    const std::string& getKey() const;

    /**
     * Set new node
     * @param value
     */
    void setKey(const std::string& value);
    
    /**
     * Get current value
     * @return value
     */
    int getInterval() const;

    /**
     * Set new value
     * @param value
     */
    void setInterval(const int value);

    /**
     * Get current value
     * @return value
     */
    double getModified() const;

    /**
     * Set new value
     * @param value
     */
    void setModified(const double value);

private:
    enum elementType {
        USERNAME = 0,
        MAIL = 1,
        PASSWORD = 2,
        URL = 3,
        PORT = 4,
        KEY = 5,
        INTERVAL = 6,
        MODIFIED = 7,
    };
    struct element elements[8] = {
        /** username is the base32 encoded mail address */
        { "username", json_type_string, new std::string(), false, false , true },
        /** mail address to generate username*/
        { "mail", json_type_string, new std::string(), false, false , false },
        /** password for ffsync server */
        { "password", json_type_string, new std::string(), false, false , true },
        /** url to ffsync auth server */
        { "url", json_type_string, new std::string(), false, false , true },
        /** port of ther ffsync storage server */
        { "port", json_type_int, new int(), false, false , true },
        /** key to encrypt and decrypt the sync data */
        { "key", json_type_string, new std::string(), false, false , false },
        /** sync time interval */
        { "interval", json_type_int, new int(), false, false , true },
        /** last modified unix timestamp for local content */
        { "modified", json_type_double, new double, false, false , true },
    };

};

#endif /* __QBL_JSON_MAIN_CONFIG_FFSYNC_USER_H__ */
