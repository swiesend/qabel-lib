/*
 * @file		qbl-json-chat-uuid-mac.h
 * @brief		Class to handle yes or no request. Also sending the mac address
 *              (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_UUID_MAC_H__
#define __QBL_JSON_CHAT_UUID_MAC_H__

#include <string>
using namespace std;

#include "qbl-json-chat.h"

/**
 *
 * class QblJsonChatUuidMac: Class to handle uuid request. Also sending the mac
 * address
 */
class QblJsonChatUuidMac: public QblJsonChat {
public:
    /**
     * Constructor to create a JSON message
     * @param sender Sender of the message
     * @param uuid UUID to send
     * @param type Type of the message
     */
    QblJsonChatUuidMac(std::string sender, int uuid,
            messageType type = NO_TYPE);
    /**
     * Destructor
     */
    virtual ~QblJsonChatUuidMac();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();

private:

};

#endif /* __QBL_JSON_CHAT_UUID_MAC_H__ */
