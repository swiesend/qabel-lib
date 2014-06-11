/*
 * @file		qbl-json-array.h
 * @brief		Main Class for a JSON array (Header File)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <string>
#include <list>
#include <exception>
#include <mutex>
using namespace std;

#include <json.h>
#include <stdarg.h>

#include "qbl-json.h"

#ifndef __QBL_JSON_ARRAY_H__
#define __QBL_JSON_ARRAY_H__

#define BUFFER_LENGTH 1024

typedef std::list<QblJsonObject *> QblJsonObjectList;

/**
 * Class QblJsonArray: Main Class for a JSON array (Header File)
 * @todo check whether a mutex is needed for adding and delete elements
 */
class QblJsonArray : public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonArray();
    /**
     * Destructor
     */
    virtual ~QblJsonArray();

    /**
     * Virtual function to parse the JSON string
     * @todo to implement
     * @param string String to parse
     * @return
     */
    virtual void parse(std::string string) = 0;
    /**
     * Virtual function to parse the JSON object
     * @param obj Object to parse
     * @return
     */
    virtual void parse(json_object *obj = NULL) = 0;
    /**
     * Delete first element from the list which is found
     * @param obj Element to delete
     * @return Deleted element or NULL if no one is found
     */
    QblJsonObject *deleteEntry(QblJsonObject *obj);
    /**
     * Find object in the list
     * @brief findObject 
     * @param obj object to search
     * @return found object or NULL if not found
     */
    QblJsonObject *findObject(QblJsonObject *obj);
    /**
     * Add an entry at the end of the list
     * @param obj Element to add
     */
    void addEntry(QblJsonObject *obj);

protected:
    QblJsonObjectList list;         /**< Array list of JSON object */

private:
    //std::mutex mutex;               /**< Mutex for handling list */
};

#endif                          /* __QBL_JSON_ARRAY_H__ */
