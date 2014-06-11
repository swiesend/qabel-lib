/*
 * @file		qbl-json-ffsync-payload.cpp
 * @brief		Class to handle the payload object (Implementation)
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
#include "qbl-json-ffsync-payload.h"

QblJsonFFSyncPayload::QblJsonFFSyncPayload()
{
    return;
}

QblJsonFFSyncPayload::~QblJsonFFSyncPayload()
{
    return;
}

void QblJsonFFSyncPayload::parse(std::string string)
{
    this->json = json_tokener_parse(string.data());
}

std::string QblJsonFFSyncPayload::getCiphertext()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "ciphertext", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncPayload::getIv()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "IV", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncPayload::getHmac()
{
    json_object *value;
    
    json_object_object_get_ex(this->json, "HMAC", &value);
    return json_object_get_string(value);
}

std::string QblJsonFFSyncPayload::createPayload(std::string ciphertext, std::string iv, std::string hmac) {
    std::string payload = "{\\\"ciphertext\\\": \\\"";
    payload += ciphertext;
    payload += "\\\", \\\"IV\\\": \\\"";
    payload += iv;
    payload += "\\\", \\\"HMAC\\\": \\\"";
    payload += hmac;
    payload += "\\\"}";
    
    return payload;
}
