/*
 * @file		qbl-json-ffsync-payload.h
 * @brief		Class to handle the ffsync record object (Header file)
 * @author		Malte Zobel <zobel@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_FFSYNC_PAYLOAD_H__
#define __QBL_JSON_FFSYNC_PAYLOAD_H__

#include <string>

#include <json_object.h>

/**
 *
 * class QblJsonFFSyncPayload: Class to handle the ffsync payload object
 *  (Header file)
 */
class QblJsonFFSyncPayload{
public:
    /**
     * Constructor
     */
    QblJsonFFSyncPayload();
    /**
     * Destructor
     */
    ~QblJsonFFSyncPayload();
    /**
     * Parse a json string into an QblJsonFFSyncPayload Object
     * @param json string
     */
    void parse(std::string);
    /**
     * Get the payload value of the parsed json string 
     * @return payload value
     */
    std::string getCiphertext();
    /**
     *Get the ID of the parsed json string 
     * @return ID
     */
    std::string getIv();
    /**
     * Get the last modified time of the parsed json string
     * @return last modified time
     */
    std::string getHmac();
    /**
     * Create a payload json string
     * @param ciphertext
     * @param iv
     * @param hmac
     * @return payload json string
     */
    std::string createPayload(std::string ciphertext, std::string iv, std::string hmac);
    
private:
    json_object *json;
};  
#endif /* __QBL_JSON_FFSYNC_PAYLOAD_H__ */
