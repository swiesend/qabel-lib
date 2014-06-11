/*
 * @file		qbl-json-chat-message-complete.h
 * @brief       Class to handle a real complete chat message (Implementation)
 * @author      Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-json-chat-message-complete.h"

#include <fcntl.h>
#include <fcntl.h>
#include <json_object.h>
#include <linkhash.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "../qbl.h"
#include "qbl-json-object.h"

QblJsonChatMessageComplete::QblJsonChatMessageComplete(json_object* obj) :
    QblJsonChatMessage()
{
    this->parse(obj);

    return;
}

QblJsonChatMessageComplete::~QblJsonChatMessageComplete()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

std::string QblJsonChatMessageComplete::getJsonString()
{
    std::string result;
    int i;

    result += QblJsonChat::getJsonString();
    result += "\"";
    result += this->elements[MESSAGE].name;
    result += "\":\"";
    result += *(std::string *) this->elements[MESSAGE].obj;
    result += "\",";

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "}";

    return (result);
}
