/*
 * @file		qbl-chat-message-send.h
 * @brief		Class to send message to recipient (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CHAT_MESSAGE_SEND_H__
#define __QBL_CHAT_MESSAGE_SEND_H__

#include "iqbl-chat-send.h"
#include "qbl-object.h"
#include "qbl-json-chat-message.h"
#include "qbl-config-inbox.h"
#include "qbl-json-main-config-contact.h"

/**
 * Class QblChatMessageSend: Class to send message to recipient
 * @brief The QblChatMessageSend class
 */
class QblChatMessageSend: public QblObject {
public:
    /**
     * Constructor
     * @param caller Caller of this class which handle the callbacks
     * @param json Message as a JSON object
     * @param contact Information about the contact
     */
    QblChatMessageSend(IQblChatSend *caller, QblJsonChat json,
            QblJsonMainConfigContact *contact);
	/**
	 * Destructor
	 */
	virtual ~QblChatMessageSend();

	/**
	 * Add message to internal message queue
	 */
    void addMessageToQueue();
    /**
     * Send message to server. Shall only called from the library
     */
    bool sendMessage();
    /**
     * Get the inbox of the recipient
     * @return Inbox of the recipient
     */
    //const std::string& getInbox() const;
    /**
     * Get the message as a JSON object
     * @return Message
     */
    QblJsonChat& getJsonString();

private:
    IQblChatSend *caller;
    QblJsonChat json;
    QblJsonMainConfigContact *contact;

    std::string createMessage();
};

#endif /* __QBL_CHAT_MESSAGE_SEND_H__ */
