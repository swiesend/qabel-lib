/*
 * @file		qbl-json-main-config-blockserver.h
 * @brief		Class to handle a block server in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_BLOCKSERVER_H__
#define __QBL_JSON_MAIN_CONFIG_BLOCKSERVER_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigBlockServer: Class to handle a block server in the main
 * configuration (Header file)
 */
class QblJsonMainConfigBlockServer: public QblJson {
public:
    /**
     * Standard constructor
     */
    QblJsonMainConfigBlockServer();
    /**
     * Constructor
     * @param server Server name
     * @param port Server port
     * @param path Server path
     */
    QblJsonMainConfigBlockServer(const std::string& server, int port = 443,
            const std::string& path = "");
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigBlockServer();

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
     * Get server name
     * @return Server name
     */
    const std::string& getServer() const;
    /**
     * Set new server name
     * @param server New server name
     */
    void setServer(const std::string& server);
    /**
     * Get server port
     * @return Server port
     */
    int getPort() const;
    /**
     * Set new server port
     * @param port Server port
     */
    void setPort(int port = 443);
    /**
     * Get server path
     * @return Server path
     */
    const std::string& getPath() const;
    /**
     * Set new server path
     * @param path New server path
     */
    void setPath(const std::string& path = "");
    /**
     * Set server URL
     * @param server New server name
     * @param port New server port
     * @param path New server path
     */
    void setUrl(const std::string& server, int port = 443,
            const std::string& path = "");
    // TODO to delete after beta release -> GUI needs to rework
    std::string getUrl();
    /**
     * Get block server authentication
     * @return block server authentication
     */
    const std::string& getAuth() const;
    /**
     * Set new block server authentication
     * @param new block server authentication
     */
    void setAuth(const std::string& auth);

private:
    enum elementType {
        SERVER = 0, 
        PORT = 1,
        PATH = 2,
        AUTH = 3,
    };
    struct element elements[4] = {
        /** server name of the block server */
        { "server", json_type_string, new std::string(), false, true, true },
        /** port of the block server */
        { "port", json_type_int, new int(), false, true, true },
        /** path on the block server */
        { "path", json_type_string, new std::string(), false, true, true },
        /** authentication of the block server */
        { "auth", json_type_string, new std::string(), false, true, true }, 
    };
};

#endif /* __QBL_JSON_MAIN_CONFIG_BLOCKSERVER_H__ */
