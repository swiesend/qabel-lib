/*
 * @file        qbl-json-chat-yn.cpp
 * @brief       Class to handle yes or no chat requests (Implementation)
 * @author      Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

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

#include "qbl.h"
#include "qbl-json-object.h"
#include "qbl-json-chat-yn.h"

QblJsonChatYN::QblJsonChatYN(std::string sender, bool value, messageType type) :
        QblJsonChat(sender, type)
{
    this->setYesNo(value);

    return;
}

QblJsonChatYN::~QblJsonChatYN()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

std::string QblJsonChatYN::getJsonString()
{
    std::string result;
    int i, elements[] = { YES_NO };

    result += QblJsonChat::getJsonString();

    for (i = 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++) {
        result += "\"";
        result += this->elements[elements[i]].name;
        result += "\":";
        if (this->elements[elements[i]].type == json_type_string) {
            result += "\"";
            result += *(std::string *) this->elements[elements[i]].obj;
            result += "\"";
        } else if (this->elements[elements[i]].type == json_type_int) {
            result += to_string(*(int *) this->elements[elements[i]].obj);
        } else if (this->elements[elements[i]].type == json_type_boolean) {
            result += to_string(*(bool *) this->elements[elements[i]].obj);
        }
        result += ",";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "}";
    return (result);
}
