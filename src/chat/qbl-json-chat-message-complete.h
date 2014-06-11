/*
 * @file		qbl-json-chat-message-complete.h
 * @brief		Class to handle a real complete chat message (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_MESSAGE_COMPLETE_H__
#define __QBL_JSON_CHAT_MESSAGE_COMPLETE_H__

#include <string>
using namespace std;

#include "qbl-json-chat-message.h"

/**
 *
 * class QblJsonChatMessageComplete: Class to handle a real chat message
 */
class QblJsonChatMessageComplete: public QblJsonChatMessage {
public:
    /**
     * Constructor to create a nearly empty chat JSON object
     */
    QblJsonChatMessageComplete(json_object* obj);
    /**
     * Destructor
     */
    virtual ~QblJsonChatMessageComplete();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();

private:

};

typedef std::list<QblJsonChatMessageComplete> QblJsonChatMessageCompleteList;

#endif /* __QBL_JSON_CHAT_MESSAGE_COMPLETE_H__ */
