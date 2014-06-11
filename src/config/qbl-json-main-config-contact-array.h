/*
 * @file		qbl-json-main-config-contact-array.h
 * @brief		Class to handle the contacts arrays in the main configuration (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_CONTACT_ARRAY_H__
#define __QBL_JSON_MAIN_CONFIG_CONTACT_ARRAY_H__

#include <string>
using namespace std;

#include "qbl-json.h"
#include "qbl-json-array.h"
#include "qbl-json-main-config-contact.h"

typedef std::list<QblJsonMainConfigContact *> QblJsonMainConfigContactList;

/**
 *
 * class QblJsonMainConfigContactArray: Class to handle the contacts in the main
 * configuration (Header file)
 */
class QblJsonMainConfigContactArray : public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigContactArray();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigContactArray();

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
     * Get the list of all found elements
     * @return
     */
    QblJsonMainConfigContactList getList();
    
    /**
     * Get contact with an specific uuid
     * @brief getContact
     * @param uuid
     * @return 
     */
    QblJsonMainConfigContact *getContact(int uuid);

private:

};

#endif /* __QBL_JSON_MAIN_CONFIG_CONTACT_ARRAY_H__ */
