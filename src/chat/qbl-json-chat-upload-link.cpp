/*
 * @file        qbl-json-chat-upload-link.cpp
 * @brief       Class to handle a link with data which have to share
 *              Implementation)
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
#include "qbl-json-chat-upload-link.h"

QblJsonChatUploadLink::QblJsonChatUploadLink(json_object *obj) :
        QblJsonChat(obj), share(NULL), blockServer(NULL), upload(NULL)
{
    this->blockServer =
        new QblJsonMainConfigBlockServer(this->getServer(), this->getPort(),
                this->getPath());
    this->upload = new QblJsonMainConfigUpload();
    this->upload->setPublic(this->getPublic());

    return;
}

QblJsonChatUploadLink::QblJsonChatUploadLink(std::string sender,
        QblJsonMainConfigShare* share) :
        QblJsonChat(sender, QblJsonChat::UPLOAD_LINK), share(share)

{
    Qbl *qbl;
    qbl = Qbl::getInstance();

    this->upload =
            qbl->getConfig()->getUploads()->getItem(this->share->getUploadId());
    this->blockServer =
            qbl->getConfig()->getBlockServers()->getItem(
                    this->upload->getBlockServerId());

    this->setServer(this->blockServer->getServer());
    this->setPort(this->blockServer->getPort());
    this->setPath(this->blockServer->getPath());
    this->setKey(this->share->getKey());
    this->setPublic(this->upload->getPublic());

    return;
}

QblJsonChatUploadLink::~QblJsonChatUploadLink()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        // TODO free memory
    }

    return;
}

std::string QblJsonChatUploadLink::getJsonString()
{
    std::string result;
    int i, elements[] = { FILE_NAME, KEY, SERVER, PORT, PATH, PUBLIC };

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
        }
        result += ",";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "}";
    return (result);
}

QblJsonMainConfigBlockServer*& QblJsonChatUploadLink::getBlockServer()
{
    return (this->blockServer);
}

QblJsonMainConfigShare*& QblJsonChatUploadLink::getShare()
{
    return (this->share);
}

QblJsonMainConfigUpload*& QblJsonChatUploadLink::getUpload()
{
    return (this->upload);
}
