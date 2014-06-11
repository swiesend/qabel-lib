/*
 * @file		qbl-json-main-config-dropserver.h
 * @brief		Class to handle a drop server in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_DROPSERVER_H__
#define __QBL_JSON_MAIN_CONFIG_DROPSERVER_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigDropServer: Class to handle a drop server in the main
 * configuration (Header file)
 */
class QblJsonMainConfigDropServer: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigDropServer();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigDropServer();

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
     * Get drop server url
     * @return drop server url
     */
    const std::string& getUrl() const;
    /**
     * Set new drop server url
     * @param new drop server url
     */
    void setUrl(const std::string& url);

    /**
     * Get drop server authentication
     * @return drop server authentication
     */
    const std::string& getAuth() const;
    /**
     * Set new drop server authentication
     * @param new drop server authentication
     */
    void setAuth(const std::string& auth);

    /**
     * Get current status of drop server
     * @return Current status
     */
    bool getActive() const;
    /**
     * Set new status of drop server
     * @param new status
     */
    void setActive(const bool value);

    /**
     * Get current value of websockets
     * @return current value
     */
    bool getWebSockets() const;
    /**
     * Set new value for websockets
     * @param new value
     */
    void setWebSockets(const bool value);

    /**
     * Get current poll interval
     * @return current poll interval
     */
    int getPollInterval() const;
    /**
     * Set new value for poll interval
     * @param new poll interval
     */
    void setPollInterval(const int value);



private:
    enum elementType {
        URL = 0,
        AUTH = 1,
        ACTIVE = 2,
        WEBSOCKETS = 3,
        POLL_INTERVAL = 4,
    };
    struct element elements[5] = {
        /** url of the drop server */
        { "url", json_type_string, new std::string(), false, true, true },
        /** authentication of the drop server */
        { "auth", json_type_string, new std::string(), false, true, true },
        /** status of the drop server */
        { "active", json_type_boolean, new bool, false, false, true },
        /** use of websockets for the drop server */
        { "websockets", json_type_boolean, new bool, false, false, true },
        /** poll interval of the drop server */
        { "poll_interval", json_type_int, new int, false, true, true },
    };
};

#endif /* __QBL_JSON_MAIN_CONFIG_DROPSERVER_H__ */
