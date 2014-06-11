/*
 * @file		qbl-json-main-config-identity-array.h
 * @brief		Class to handle the identities arrays in the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_IDENTITY_ARRAY_H__
#define __QBL_JSON_MAIN_CONFIG_IDENTITY_ARRAY_H__

#include <string>
using namespace std;

#include "qbl-json.h"
#include "qbl-json-array.h"
#include "qbl-json-main-config-identity.h"

typedef std::list<QblJsonMainConfigIdentity *> QblJsonMainConfigIdentityList;
/**
 *
 * class QblJsonMainConfigIdentityArray: Class to handle the identities in the main
 * configuration (Header file)
 */
class QblJsonMainConfigIdentityArray: public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigIdentityArray();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigIdentityArray();

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
     * @brief addIdentity
     * @param alias Alias of the identity
     * @param privateKey private key of the identity
     * @param publicKey public key of the identity
     * @param inbox inbox of the identity
     */
    void addIdentity(const std::string& alias, const std::string& privateKey,
            const std::string& publicKey, const std::string& inbox);
    /**
     * Get the list of all found elements
     * @return
     */
    QblJsonMainConfigIdentityList getList();

private:

};

#endif /* __QBL_JSON_MAIN_CONFIG_IDENTITY_ARRAY_H__ */
