/*
 * @file		qbl-json-block-storage-new.h
 * @brief		Class to handle the received storage request JSON configuration
 *              (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_BLOCK_NEW_STORAGE_H__
#define __QBL_JSON_BLOCK_NEW_STORAGE_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonBlockStorageNew: Class to handle the received storage request
 * JSON configuration
 */
class QblJsonBlockStorageNew : public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonBlockStorageNew();
    /**
     * Destructor
     */
    virtual ~QblJsonBlockStorageNew();

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
    const std::string& getPublic() const;
    void setPublic(const std::string& _public);
    const std::string& getToken() const;
    void setToken(const std::string& token);
    const std::string& getRevokeToken() const;
    void setRevokeToken(const std::string& revokeToken);

private:
    enum elementType {
        PUBLIC = 0,
        TOKEN = 1,
        REVOKE_TOKEN = 2,
    };
    struct element elements[3] = {
        /** public of the account */
        { "public", json_type_string, new std::string(), false, true, true },
        /** token name of the account */
        { "token", json_type_string, new std::string(), false, true, true },
        /** authentication of the account */
        { "revoke_token", json_type_string, new std::string(), false, true, true },
    };
};

#endif /* __QBL_JSON_BLOCK_NEW_STORAGE_H__ */
