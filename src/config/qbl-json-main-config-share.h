/*
 * @file		qbl-json-main-config-share.h
 * @brief		Class to handle a share in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_SHARE_H__
#define __QBL_JSON_MAIN_CONFIG_SHARE_H__

#include <string>
#include <list>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigShare: Class to handle a share in the main
 * configuration (Header file)
 * TODO: add and remove contacts to or from list
 */
class QblJsonMainConfigShare: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigShare();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigShare();

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
    const std::string& getBasedir() const;
    void setBasedir(const std::string& basedir);
    int getUploadId() const;
    void setUploadId(int uploadId);
    int getAliasId() const;
    void setAliasId(int aliasId);
    std::list<int> *getContacts() const;
    void setContacts(std::list<int> contacts);
    const std::string& getKey() const;
    void setKey(const std::string& key);

private:
    enum elementType {
        BASEDIR = 0,
        KEY = 1,
        UPLOAD_ID = 2,
        ALIAS_ID = 3,
        CONTACTS = 4,
    };
    struct element elements[5] = {
        { "basedir", json_type_string, new std::string(), false, false,
            false },
        { "key", json_type_string, new std::string(), false, false, false },
        { "upload_id", json_type_int, new int(), false, false, false },
        { "alias_id", json_type_int, new int(), false, false, false },
        { "contacts", json_type_array, new std::list<int>(), false, false,
            false },
    };

    void parseContactArray(json_object *obj);
};

#endif /* __QBL_JSON_MAIN_CONFIG_SHARE_H__ */
