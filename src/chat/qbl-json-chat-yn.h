/*
 * @file		qbl-json-chat-yn.h
 * @brief		Class to handle yes or no request (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_YN_H__
#define __QBL_JSON_CHAT_YN_H__

#include <string>
using namespace std;

#include "qbl-json-chat.h"

/**
 *
 * class QblJsonChatYN: Class to handle yes or no request
 * share
 */
class QblJsonChatYN: public QblJsonChat {
public:
    /**
     * Constructor to create a nearly empty chat JSON object
     */
    //QblJsonChatYN();
    /**
     * Constructor to create a JSON message
     * @param sender Sender of the message
     * @param type Type of the message
     * @param value Value
     */
    QblJsonChatYN(std::string sender, bool value, messageType type = NO_TYPE);
    /**
     * Destructor
     */
    virtual ~QblJsonChatYN();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();

private:

};

#endif /* __QBL_JSON_CHAT_YN_H__ */
