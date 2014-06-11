/*
 * @file		qbl-json-main-config-upload.h
 * @brief		Class to handle an upload in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_UPLOAD_H__
#define __QBL_JSON_MAIN_CONFIG_UPLOAD_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigUpload: Class to handle an upload in the main
 * configuration (Header file)
 */
class QblJsonMainConfigUpload: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigUpload();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigUpload();

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
    int getBlockServerId() const;
    void setBlockServerId(int blockserverid);
    const std::string& getPublic() const;
    void setPublic(const std::string& value);
    const std::string& getToken() const;
    void setToken(const std::string& token);
    const std::string& getRevokeToken() const;
    void setRevokeToken(const std::string& revokeToken);

private:
	enum elementType {
        BLOCK_SERVER_ID = 0,
        PUBLIC = 1,
        TOKEN = 2,
        REVOKE_TOKEN = 3,
    };
    
    struct element elements[4] = {
        { "block_server_id", json_type_int, new int(), false, false , false },
        { "public", json_type_string, new std::string(), false, false , false },
        { "token", json_type_string, new std::string(), false, false , false },
        { "revoke_token", json_type_string, new std::string(), false, false,
            false },
    };
    std::string token;
    std::string RevokeToken;
};

#endif /* __QBL_JSON_MAIN_CONFIG_UPLOAD_H__ */
