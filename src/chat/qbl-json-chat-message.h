/*
 * @file		qbl-json-chat-message.h
 * @brief		Class to handle a real chat message (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_MESSAGE_H__
#define __QBL_JSON_CHAT_MESSAGE_H__

#include <string>
using namespace std;

#include "qbl-json-chat.h"

/**
 *
 * class QblJsonChatMessage: Class to handle a real chat message
 */
class QblJsonChatMessage: public QblJsonChat {
public:
    /**
     * Constructor to create a nearly empty chat JSON object
     */
    QblJsonChatMessage();
    /**
     * Constructor to create a nearly empty chat JSON object
     * @param obj
     */
    QblJsonChatMessage(json_object *obj);
    /**
     * Constructor to create a nearly empty chat JSON object
	 * @param sender Sender of the message
     * @param type Message type
     */
    QblJsonChatMessage(std::string sender, std::string message, time_t date);
    /**
     * Destructor
     */
    virtual ~QblJsonChatMessage();

    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    /**
     * Get current message
     * @return Current message
     */
    const std::string& getMessage() const;
    /**
     * Set new message
     * @param message New message
     */
    void setMessage(const std::string& message);
    /**
     * Get time stamp message was sent
     * @return Time stamp
     */
    time_t getMessageDate() const;
    /**
     * Set message date
     * @param messageDate Time stamp message created
     */
    void setMessageDate(time_t messageDate);

private:

};

#endif /* __QBL_JSON_CHAT_MESSAGE_H__ */
