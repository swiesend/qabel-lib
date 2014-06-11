/*
 * @file		qbl-json-main-config-upload-array.h
 * @brief		Class to handle the upload array in the main configuration
 *              (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *      		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_UPLOAD_ARRAY_H__
#define __QBL_JSON_MAIN_CONFIG_UPLOAD_ARRAY_H__

#include <string>
using namespace std;

#include "qbl-json.h"
#include "qbl-json-array.h"
#include "qbl-json-main-config-upload.h"

typedef std::list<QblJsonMainConfigUpload *> QblJsonMainConfigUploadList;

/**
 *
 * class QblJsonMainConfigUploadArray: Class to handle the upload array in the
 * main configuration
 */
class QblJsonMainConfigUploadArray: public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigUploadArray();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigUploadArray();

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
    QblJsonMainConfigUploadList getList();
    /**
     * Get Upload config item
     * @param id Uuid of the entry
     * @return Upload config item
     */
    QblJsonMainConfigUpload *getItem(int64_t id);

private:

};

#endif /* __QBL_JSON_MAIN_CONFIG_UPLOAD_ARRAY_H__ */
