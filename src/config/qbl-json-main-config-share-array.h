/*
 * @file		qbl-json-main-config-share-array.h
 * @brief		Class to handle the share array in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_SHARE_ARRAY_H__
#define __QBL_JSON_MAIN_CONFIG_SHARE_ARRAY_H__

#include <string>
using namespace std;

#include "qbl-json.h"
#include "qbl-json-array.h"
#include "qbl-json-main-config-share.h"

typedef std::list<QblJsonMainConfigShare *> QblJsonMainConfigShareList;
/**
 *
 * class QblJsonMainConfigShareArray: Class to handle the share array in the main
 * configuration (Header file)
 */
class QblJsonMainConfigShareArray: public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigShareArray();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigShareArray();

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
    QblJsonMainConfigShareList getList();

private:

};

#endif /* __QBL_JSON_MAIN_CONFIG_SHARE_ARRAY_H__ */
