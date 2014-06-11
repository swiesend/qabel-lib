/*
 * @file		qbl-json.cpp
 * @brief		Main Class for the JSON de- and serialising (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <json_tokener.h>
#include <string.h>
#include <time.h>
#include <string.h>

#include "qbl.h"
#include "qbl-json.h"

#define BUFFER_LENGTH 1024

QblJson::QblJson() :
        QblJsonObject()
{

    return;
}

QblJson::~QblJson()
{

    return;
}

void QblJson::parse(std::string string)
{
    this->obj = json_tokener_parse(string.data());
    if (this->obj == NULL) {
        throw QblException{"Cannot parse JSON string:\n%s\n", string.data()};
    }

    return;
}

std::string QblJson::getJsonString(element *elem) {

    std::string result;
    size_t pos;
    json_type type = elem->type;
    result += "\"";
    result += elem->name;
    result += "\":";
    switch(type) {
    case json_type_boolean:
        if ((*(bool*)elem->obj) == true) {
            result += "true";
        }
        else {
            result += "false";
        }
        break;

    case json_type_int:
        result += std::to_string(*(int*)elem->obj);
        break;
    case json_type_string:
        result += "\"";
        result += *(std::string *)elem->obj;
        result += "\"";
        break;
    case json_type_double:
        result += std::to_string(*(double*)elem->obj);
        pos = result.find(",");
        if(pos != string::npos)
        {
            result.replace(pos, 1, ".");
        }
        break;
    //default:
    }

    return (result);
}

std::string QblJson::getJsonString()
{
    std::string result;
    int buffer_length = 20;

    result = "\"uuid\":" + std::to_string(this->getUuid()) + ",";

    result += "\"updated\":";
    result += std::to_string(this->getCreated());
    result += ",";

    result += "\"created\":";
    result += std::to_string(this->getUpdated());
    result += ",";

    result += "\"deleted\":";
    result += std::to_string(this->getDeleted());
    result += ",";

    return (result);
}
