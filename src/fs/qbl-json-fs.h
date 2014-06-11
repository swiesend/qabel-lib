/*
 * @file		qbl-json-fs.h
 * @brief		Class to cache file information for reuse (Header file)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_FS_H__
#define __QBL_JSON_FS_H__

#include <string>
#include <list>
using namespace std;

#include "qbl-json.h"

/**
 *
 * class QblJsonFs: Class to handle a share in the main
 * configuration (Header file)
 */
class QblJsonFs: public QblJson {
public:
    /**
     * Constructor
     */
    QblJsonFs();
    /**
     * Destructor
     */
    virtual ~QblJsonFs();

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
    int getModDate() const;
    void setModDate(int modDate);
    const std::string& getName() const;
    void setName(const std::string& name);

private:
    enum elementType {
        NAME = 0,
        MOD_DATE = 1,
    };
    struct element elements[2] = {
        { "name", json_type_string, new std::string(), false, false,
            false },
        { "mod_date", json_type_int, new int(), false, false, false },
    };

};

#endif /* __QBL_JSON_FS_H__ */
