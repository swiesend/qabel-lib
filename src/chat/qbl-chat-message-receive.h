/*
 * @file		qbl-chat-message-receive.h
 * @brief		Class to receive message from "server" (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CHAT_MESSAGE_RECEIVE_H__
#define __QBL_CHAT_MESSAGE_RECEIVE_H__

#include "qbl-object.h"
#include "qbl-config-inbox.h"
#include "qbl-json-main-config-identity.h"
#include "qbl-json-chat.h"

/**
 * Class QblChatMessageReceive: Class to receive message from "server"
 * @brief The QblChatMessageReceive class
 */
class QblChatMessageReceive: public QblObject {
public:
    /**
     * Constructor
     * @param caller
     * @param account
     */
	QblChatMessageReceive(QblJsonMainConfigIdentity *identity);
	/**
	 * Destructor
	 */
	virtual ~QblChatMessageReceive();

    /**
     * Send message to server. Shall only called from the library
     * @todo error handling when no connection
     * @todo add message to history and forward message to client
     */
    bool sendMessage();

private:
    QblJsonMainConfigIdentity *identity;
    //QblJsonChatArray *chatArray;

    /**
     * Create the HTTP message which shall send to "server"
     * @return Message as a string
     */
    std::string createMessage();
    /**
     * Check the received message and switch it to the different messages
     * @param message Received message
     * @param length Length of the message
     * @return 0 = success
     */
    int checkReceivedMessage(std::string msg);
    /**
     * Handle received chat message
     * @param chat Received chat message extract from complete message
     * @return 0 == successful
     */
    int handleReceivedChatMessage(QblJsonChat *chat);
};

#endif /* __QBL_CHAT_MESSAGE_RECEIVE_H__ */
