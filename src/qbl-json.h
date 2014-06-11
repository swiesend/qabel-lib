/*
 * @file		qbl-json.h
 * @brief		Main Class for the JSON de- and serialising (Header File)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_H__
#define __QBL_JSON_H__

#include <json.h>
#include <stdarg.h>

#include <string>
#include <list>
#include <exception>
using namespace std;

#include "qbl-json-object.h"

/**
 * Class QblJson: Main class for JSON de- and serialising
 */
class QblJson : public QblJsonObject {
public:
    /**
     * Constructor
     */
    QblJson();
    /**
     * Destructor
     */
    virtual ~QblJson();

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
     * Get JSON object
     * @param element to write to string
     * @return JSON string
     */
    virtual std::string getJsonString(element *elem);
    /**
     * Get JSON object
     * @return JSON string
     */
    virtual std::string getJsonString() = 0;
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    virtual void integrate(QblJson *other) = 0;

protected:

private:

};

#endif                          /* __QBL_JSON_H__ */
