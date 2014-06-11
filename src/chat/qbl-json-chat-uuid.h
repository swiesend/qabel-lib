/*
 * @file		qbl-json-chat-uuid.h
 * @brief		Class to handle yes or no request (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_UUID_H__
#define __QBL_JSON_CHAT_UUID_H__

#include <string>
using namespace std;

#include "qbl-json-chat.h"

/**
 *
 * class QblJsonChatUuid: Class to handle uuid request
 * share
 */
class QblJsonChatUuid: public QblJsonChat {
public:
    /**
     * Constructor to create a nearly empty chat JSON object
     */
    //QblJsonChatUuid();
    /**
     * @param type Type of the message
     * @param value Value
     */
    /**
     * Constructor to create a JSON message
     * @param sender Sender of the message
     * @param uuid UUID to send
     * @param type Type of the message
     */
    QblJsonChatUuid(std::string sender, int uuid, messageType type = NO_TYPE);
    /**
     * Destructor
     */
    virtual ~QblJsonChatUuid();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();

private:

};

#endif /* __QBL_JSON_CHAT_UUID_H__ */
