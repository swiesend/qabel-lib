/*
 * @file		qbl-json-object.h
 * @brief		Main Class for the JSON stuff (Header File)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <string>
#include <list>
#include <exception>
using namespace std;

#include <json.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef __QBL_JSON_OBJECT_H__
#define __QBL_JSON_OBJECT_H__

#define BUFFER_LENGTH 1024

#define EQUAL_UUID  1 << 0          /**< UUID are equal */
#define EQUAL_DATE  1 << 1          /**< Date is equal */
#define DATE_NEWER  1 << 2          /**< Date of the other is newer */

/**
 * Class QblJsonException: Main exception for the Qbl JSON classes
 */
class QblJsonException: public exception {
public:
    /**
     * Constructor
     * @param msg Error message
     */
    QblJsonException(const char *msg, ...)
    {
        va_list list;

        va_start(list, msg);
        vsnprintf(this->msg, BUFFER_LENGTH, msg, list);
        va_end(list);

        return;
    }

    /**
     * What was the error
     * @return Error message
     */
    const char *what() const throw ()
    {
        return (msg);
    }

private:
    char msg[BUFFER_LENGTH];
};

/**
 * Class QblJsonObject: Main class for JSON de- and serialising
 */
class QblJsonObject {
public:
    bool parse(const char *key, json_object *value);
    /**
     * Name and type of the JSON element
     */
    struct element {
        const char *name;           /**< Name of the element */
        enum json_type type;        /**< Type of the element */
        void *obj;                  /**< Object have to use */
        bool checked;               /**< This element is found in
        						      configuration string */
        bool mandatory;             /**< This element is mandatory */
        bool syncronised;           /**< This element shall syncronised on
                                       Firefox Sync */
    };

    /**
     * Constructor
     */
    QblJsonObject();
    /**
     * Destructor
     */
    virtual ~QblJsonObject();

    int64_t getUuid() const;
    time_t getCreated() const;
    time_t getDeleted() const;
    time_t getUpdated() const;

    /**
     * Compare two JSON objects
     * @param other The other JSON object
     * @return Result of the comparison
     */
    uint8_t compare(QblJsonObject *other);
    /**
     * Check whether UUID is equal with the compared one
     * @param compareResult Received result from comparison
     * @return true UUID are the same
     */
    static bool isUuidEqual(uint8_t compareResult);
    /**
     * Check whether date is equal with the compared one
     * @param compareResult Received result from comparison
     * @return true Date are the same
     */
    static bool isDateEqual(uint8_t compareResult);
    /**
     * Check whether date of the other is newer
     * @param compareResult Received result from comparison
     * @return true Date is newer
     */
    static bool isDateNewer(uint8_t compareResult);

protected:
    json_object * obj;              /**< Main JSON object */

    /**
     * Check whether key is a default key and set this value
     * @param key Key to check
     * @param value Value to set
     * @return found one == true
     */
    //bool parse(const char *key, json_object *value);
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    void integrate(QblJsonObject *other);
    /**
     * Add a list of string values to the JSON string
     * @param obj Object to set
     * @param list List to add
     * @todo to implement
     * @return bool == everything okay
     */
    bool addStringList(json_object * obj, std::list<std::string> list);
    /**
     * Get a list of string values
     * @param obj Object to parse
     * @return String list
     */
    std::list<std::string> getStringList(json_object * obj)
            throw (QblJsonException &);
    /**
     * Add a list of integer values to the JSON string
     * @param obj Object to set
     * @param list List to add
     * @todo to implement
     * @return bool == everything okay
     */
    bool addIntList(json_object * obj, std::list<int> list);
    /**
     * Get a list of integer values
     * @param obj Object to parse
     * @return Integer list
     */
    std::list<int> getIntList(json_object * obj) throw (QblJsonException &);
    /**
     * Add a list of double values to JSON string
     * @param obj Object to set
     * @param list List to add
     * @return bool == everything okay
     * @todo to implement
     */
    bool addDoubleList(json_object * obj, std::list<double> list);
    /**
     * Get a list of double values
     * @param obj Object to parse
     * @return Double list
     */
    std::list<double> getDoubleList(json_object * obj)
            throw (QblJsonException &);

private:
    /**
     * UUID for this entry
     */
    int64_t uuid;                   /**< individual id of every entry */
    time_t created;                 /**< Time stamp when entry was created */
    time_t updated;                 /**< Time stamp when entry was the last
                                       modified */
    time_t deleted;                 /**< Time stamp when entry was deleted */

    /**
     * Create a random id
     * @todo Only implemented for Linux desktop
     */
    void createUuid();
    /**
     * Set new UUID
     * @todo Only implemented for Linux desktop
     * @param uuid New UUID
     */
    void setUuid(int64_t uuid);
    /**
     * Set time stamp when item is created
     * @param timestamp Time stamp to set
     */
    void setCreated(time_t timestamp);
    /**
     * Set last modification time stamp
     * @param timestamp New time stamp
     * @return 0 == okay
     */
    int setCreated(const char *timestamp);
    /**
     * Set time stamp when item is updated the last time
     * @param timestamp Time stamp to set
     */
    void setUpdated(time_t timestamp);
    /**
     * Set last modification time stamp
     * @param timestamp New time stamp
     * @return 0 == okay
     */
    int setUpdated(const char *timestamp);
    /**
     * Set time stamp when item is deleted
     * @param timestamp Time stamp to set
     */
    void setDeleted(time_t timestamp);
    /**
     * Set last modification time stamp
     * @param timestamp New time stamp
     * @return 0 == okay
     */
    int setDeleted(const char *timestamp);
};

#endif                          /* __QBL_JSON_OBJECT_H__ */
