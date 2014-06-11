/*
 * @file		qbl-json-main-config-group.h
 * @brief		Class to handle a group in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_GROUP_H__
#define __QBL_JSON_MAIN_CONFIG_GROUP_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigGroup: Class to handle a group in the main
 * configuration (Header file)
 */
class QblJsonMainConfigGroup: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigGroup();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigGroup();

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
     * Get group alias
     * @return group alias
     */
    const std::string& getAlias() const;
    /**
     * Set group alias
     * @param new group alias
     */
    void setAlias(const std::string& url);

    /**
     * Get group ps_key
     * @return group ps_kay
     */
    const std::string& getPsKey() const;
    /**
     * Set new group ps_key
     * @param new ps_key
     */
    void setPsKey(const std::string& auth);

    /**
     * Get group inbox
     * @return group inbox
     */
    const std::string& getInbox() const;
    /**
     * Set new group inbox
     * @param new inbox
     */
    void setInbox(const std::string& auth);

private:
    enum elementType {
        ALIAS = 0,
        PS_KEY = 1,
        INBOX = 2,
    };
    struct element elements[3] = {
        /** alias of the group */
        { "alias", json_type_string, new std::string(), false, true, true },
        /** key of the group */
        { "ps_key", json_type_string, new std::string(), false, true, true  },
        /** inbox of the group */
        { "inbox", json_type_string, new std::string(), false, true, true  },
    };
};

#endif /* __QBL_JSON_MAIN_CONFIG_GROUP_H__ */
