/*
 * @file		qbl-json-chat-upload-link.h
 * @brief		Class to handle a link with data which have to share (Header
 *              file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_UPLOAD_LINK_H__
#define __QBL_JSON_CHAT_UPLOAD_LINK_H__

#include <string>
using namespace std;

#include "qbl-json-chat.h"
#include "qbl-json-main-config-share.h"
#include "qbl-json-main-config-upload.h"
#include "qbl-json-main-config-blockserver.h"

/**
 *
 * class QblJsonChatUploadLink: Class to handle a link with data which have to
 * share
 */
class QblJsonChatUploadLink: public QblJsonChat {
public:
    /**
     * Constructor to create a nearly empty chat JSON object
     */
    //QblJsonChatUploadLink();
    /**
     * Constructor which handle a JSON object
     * @param obj
     */
    QblJsonChatUploadLink(json_object *obj);
    /**
     * Constructor to create a JSON message
     * @param sender
     * @param share
     */
    QblJsonChatUploadLink(std::string sender, QblJsonMainConfigShare *share);
    /**
     * Destructor
     */
    virtual ~QblJsonChatUploadLink();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    QblJsonMainConfigBlockServer*& getBlockServer();
    QblJsonMainConfigShare*& getShare();
    QblJsonMainConfigUpload*& getUpload();

private:
    QblJsonMainConfigShare *share;
    QblJsonMainConfigBlockServer *blockServer;
    QblJsonMainConfigUpload *upload;

};

#endif /* __QBL_JSON_CHAT_UPLOAD_LINK_H__ */
