/*
 * @file		qbl-json-ffsync-record.h
 * @brief		Class to handle the ffsync record object (Header file)
 * @author		Malte Zobel <zobel@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_FFSYNC_RECORD_H__
#define __QBL_JSON_FFSYNC_RECORD_H__

#include <string>

#include <json_object.h>
//#include "qbl-json.h"

/**
 *
 * class QblJsonFFSyncRecord: Class to handle the ffsync record object
 *  (Header file)
 */
class QblJsonFFSyncRecord {
public:
    /**
     * Constructor
     */
    QblJsonFFSyncRecord();
    /**
     * Destructor
     */
    ~QblJsonFFSyncRecord();
    /**
     * Parse a json string into an QblJsonFFSyncRecord Object
     * @param json string
     */
    void parse(std::string);
    /**
     * Get the payload value of the parsed json string 
     * @return payload value
     */
    std::string getPayload();
    /**
     *Get the ID of the parsed json string 
     * @return ID
     */
    std::string getId();
    /**
     * Get the last modified time of the parsed json string
     * @return last modified time
     */
    std::string getModified();
    /**
     * Create a record json string
     * @param payload
     * @param time
     * @param id
     * @return record json string
     */
    std::string createRecord(std::string payload, std::string time,
            std::string id);

private:
    json_object *json;
};
#endif /* __QBL_JSON_FFSYNC_RECORD_H__ */
