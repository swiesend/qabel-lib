/*
 * @file		qbl-json-ffsync.cpp
 * @brief		Class to handle the record object (Implementation)
 * @author		Malte Zobel <zobel@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <iostream>
#include <json_tokener.h>

#include "qbl-json.h"
#include <json.h>
#include "qbl-json-ffsync-record.h"

QblJsonFFSyncRecord::QblJsonFFSyncRecord()
{

    return;
}

QblJsonFFSyncRecord::~QblJsonFFSyncRecord()
{
    return;
}

void QblJsonFFSyncRecord::parse(std::string string)
{
    this->json = json_tokener_parse(string.data());
}

std::string QblJsonFFSyncRecord::getPayload()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "payload", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncRecord::getId()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "id", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncRecord::getModified()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "modified", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncRecord::createRecord(std::string payload,
        std::string time, std::string id)
{
    std::string record = "{\"payload\": \"";
    record += payload;
    record += "\", \"modified\": ";
    record += time;
    record += ", \"id\": \"";
    record += id;
    record += "\"}";

    return record;
}
