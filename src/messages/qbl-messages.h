/**
 * @file		qbl-messages.h
 * @brief		Class to handle messages (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_MESSAGES_H__
#define __QBL_MESSAGES_H__

#include <list>
#include <ctime>
#include <string>
using namespace std;

#include "qbl-message.h"
#include "iqbl-messages.h"

/**
 * Class to handle messages
 */
class QblMessages {
public:
    /**
     * Constructor
     */
    QblMessages();
    /**
     * Destructor;
     */
    virtual ~QblMessages();

    /**
     * Add a message to queue
     * @param message Message to add
     */
    void addMessage(QblMessage message);
    /**
     * Add a message to queue
     * @param timestamp Time stamp of the message
     * @param type Type of the message
     * @param contentType Content type of the message
     */
    void addMessage(std::time_t timestamp, QblMessage::type type,
            QblMessage::contentType contentType);
    /**
     * Get the last message from queue
     * @return QblMessage object
     */
    QblMessage getLastMessage();
    /**
     * Get a list of messages
     * @param count List length (default value: 10)
     * @return QblMessage list
     */
    std::list<QblMessage> getMessages(int count = 10);
    /**
     * Get a list of all messages
     * @return QblMessage list
     */
    std::list<QblMessage> getAllMessages();

    /**
     * Get length of the list
     * @return List length
     */
    int getListLength() const;
    /**
     * Set the length of the list
     * @param listLength New length of the list (default 10)
     */
    void setListLength(int listLength);

    /**
     * Add a listener which want to receive the last message when a new
     * message come in
     * @param listener Listener to add
     */
    void addListener(IQblMessages *listener);
    /**
     * Remove the listener
     * @param listener Listener to remove
     */
    void removeListener(IQblMessages *listener);

private:
    std::list<QblMessage> messages; /**< Message list */
    int listLength;                 /**< Max size of the list */
    std::list<IQblMessages *> listeners; /**< Listener list that wants to
                                            receive messages */

};

#endif                          /* __QBL_MESSAGES_H__ */
