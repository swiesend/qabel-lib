/*
 * @file		qbl-json-main-config-account.h
 * @brief		Class to handle the accounts in the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_ACCOUNT_H__
#define __QBL_JSON_MAIN_CONFIG_ACCOUNT_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigAccount: Class to handle the accounts in the main
 * configuration (Header file)
 */
class QblJsonMainConfigAccount : public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigAccount();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigAccount();

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
     * Get account provider
     * @return account provider
     */
    const std::string& getProvider() const;
    /**
     * Set new account provider
     * @param new account provider
     */
    void setProvider(const std::string& provider);
    /**
     * Get account user
     * @return account user
     */
    const std::string& getUser() const;
    /**
     * Set new account user
     * @param new account user
     */
    void setUser(const std::string& user);
    /**
     * Get account authentication
     * @return account authentication
     */
    const std::string& getAuth() const;
    /**
     * Set new account authentication
     * @param new account authentication
     */
    void setAuth(const std::string& auth);
private:
    enum elementType {
        PROVIDER = 0,
        USER = 1,
        AUTH = 2,
    };
    struct element elements[3] = {
        /** provider of the account */
        { "provider", json_type_string, new std::string(), false, true, true },
        /** user name of the account */
        { "user", json_type_string, new std::string(), false, true, true },
        /** authentication of the account */
        { "auth", json_type_string, new std::string(), false, true, true },
    };
};

#endif /* __QBL_JSON_MAIN_CONFIG_ACCOUNT_H__ */
