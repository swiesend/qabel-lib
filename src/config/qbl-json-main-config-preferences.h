/*
 * @file		qbl-json-main-config-preferences.h
 * @brief		Class to handle the preferences in the main configuration (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_MAIN_CONFIG_PREFERENCES_H__
#define __QBL_JSON_MAIN_CONFIG_PREFERENCES_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonMainConfigPreferences: Class to handle the preferences in the main
 * configuration (Header file)
 */
class QblJsonMainConfigPreferences: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonMainConfigPreferences();
    /**
     * Destructor
     */
    virtual ~QblJsonMainConfigPreferences();

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
     * Get current value of the use_websockets option
     * @return Current value
     */
    bool getUseWebSockets() const;
    /**
     * Set new value for the use_websockets option
     * @param new value
     */
    void setUseWebSockets(const bool value);

    /**
     * Get current default_poll_interval
     * @return Current value
     */
    int getDefaultPollInterval() const;
    /**
     * Set new default_poll_interval
     * @param new value
     */
    void setDefaultPollInterval (const int value);

    /**
     * Get current value of start_minimized
     * @return current value
     */
    bool getStartMinimized() const;
    /**
     * Set new value for start_minimized
     * @param new value
     */
    void setStartMinimized(const bool value);

    /**
     * Get current firefox sync url
     * @return Current ffsync_url
     */
    const std::string& getFFsyncUrl() const;
    /**
     * Set new firefox sync url
     * @param new ffsync_url
     */
    void setFFsyncUrl(const std::string& ffsyncUrl);

    /**
     * Get current firefox sync authentication
     * @return Current ffsync_auth
     */
    const std::string& getFFsyncAuth() const;
    /**
     * Set new firefox sync authentication
     * @param new ffsync_auth
     */
    void setFFsyncAuth(const std::string& ffsyncAuth);

    /**
     * Get current desktop_x
     * @return Current desktop_x
     */
    const std::string& getDesktopX() const;
    /**
     * Set new desktop_x
     * @param new desktop_x
     */
    void setDesktopX(const std::string& desktopX);

    /**
     * Get current desktop_y
     * @return Current desktop_y
     */
    const std::string& getDesktopY() const;
    /**
     * Set new desktop_y
     * @param new desktop_y
     */
    void setDesktopY(const std::string& desktopY);

    /**
     * Get current desktop_width
     * @return Current desktop_width
     */
    const std::string& getDesktopWidth() const;
    /**
     * Set new desktop_width
     * @param new desktop_width
     */
    void setDesktopWidth(const std::string& desktopWidth);

    /**
     * Get current desktop_height
     * @return Current desktop_height
     */
    const std::string& getDesktopHeight() const;
    /**
     * Set new desktop_height
     * @param new desktop_height
     */
    void setDesktopHeight(const std::string& desktopHeight);

private:
    enum elementType {
        USE_WEBSOCKETS = 0,
        DEFAULT_POLL_INTERVAL = 1,
        START_MINIMIZED = 2,
        FFSYNC_URL = 3,
        FFSYNC_AUTH = 4,
        DESKTOP_X = 5,
        DESKTOP_Y = 6,
        DESKTOP_WIDTH = 7,
        DESKTOP_HEIGHT= 8,
    };
    struct element elements[9] = {
        /** use_websockets of the preferences */
        { "use_websockets", json_type_boolean, new bool(false), false, false , false },
        /** default_poll_interval of the preferences */
        { "default_poll_interval", json_type_int, new int(100), false, false , false },
        /** start_minimized of the preferences */
        { "start_minimized", json_type_boolean, new bool(false), false, false , false },
        /** ffsync_url of the preferences */
        { "ffsync_url", json_type_string, new std::string(), false, true , false },
        /** ffsync_auth of the preferences */
        { "ffsync_auth", json_type_string, new std::string(), false, true , false },
        /** desktop_x of the preferences */
        { "desktop_x", json_type_string, new std::string(), false, false , false },
        /** desktop_y of the preferences */
        { "desktop_y", json_type_string, new std::string(), false, false , false },
        /** desktop_width of the preferences */
        { "desktop_width", json_type_string, new std::string(), false, false , false },
        /** desktop_height of the preferences */
        { "desktop_height", json_type_string, new std::string(), false, false , false },
    };
};

#endif /* __QBL_JSON_MAIN_CONFIG_PREFERENCES_H__ */
