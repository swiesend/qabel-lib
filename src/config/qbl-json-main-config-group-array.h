/*
 * @file		qbl-json-main-config-group-array.h
 * @brief		Class to handle the group array in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_GROUP_ARRAY_H__
#define __QBL_JSON_MAIN_CONFIG_GROUP_ARRAY_H__

#include <string>
using namespace std;

#include "qbl-json.h"
#include "qbl-json-array.h"
#include "qbl-json-main-config-group.h"

/**
 *
 * class QblJsonMainConfigGroupArray: Class to handle the group array in the main
 * configuration (Header file)
 */
class QblJsonMainConfigGroupArray: public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigGroupArray();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigGroupArray();

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
    std::list<QblJsonMainConfigGroup *> getList();

private:

};

#endif /* __QBL_JSON_MAIN_CONFIG_GROUP_ARRAY_H__ */
