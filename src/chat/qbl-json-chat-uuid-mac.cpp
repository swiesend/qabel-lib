/*
 * @file        qbl-json-chat-uuid-mac.cpp
 * @brief       Class to handle uuid chat requests. Also sending the mac address
 *              (Implementation)
 * @author      Michael Ott <michael@king-coder.de>
 *
 * copyright:   (C) 2014 by Qabel GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#include "qbl-json-chat-uuid-mac.h"

QblJsonChatUuidMac::QblJsonChatUuidMac(std::string sender, int uuid,
        messageType type) :
        QblJsonChat(sender, type)
{
    this->setUuidToSend(uuid);
    this->setMac();

    return;
}

QblJsonChatUuidMac::~QblJsonChatUuidMac()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

std::string QblJsonChatUuidMac::getJsonString()
{
    std::string result;
    int i, elements[] = { UUID_TO_SEND, MAC };

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
