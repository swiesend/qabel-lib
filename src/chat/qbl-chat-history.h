/*
 * @file		qbl-chat-history.h
 * @brief		Class to handle chat history (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CHAT_HISTORY_H__
#define __QBL_CHAT_HISTORY_H__

#include <list>

#include "qbl-json-main-config-contact.h"
#include "qbl-json-chat-message-complete.h"

class IQblChatReceive;

class QblJsonChatArray;
class QblJsonMainConfigContact;

/**
 * Class QblChatHistory: Class to handle chat history
 */
class QblChatHistory {
public:
    /**
     * Constructor
     */
    QblChatHistory();
    /**
     * Destructor
     */
    virtual ~QblChatHistory();

    /**
     * Set listener for new chat messages
     * @param listener
     */
    void addListener(IQblChatReceive *listener);
    /**
     * Remove listener for new chat messages
     * @param listener
     */
    void removeListener();
    /**
     * Add contact to the list which want history updates
     * @param contact Contact
     */
    void addContact(QblJsonMainConfigContact *contact);
    /**
     * Remove contact from list which want history updates
     * @param contact Contact
     */
    void removeContact(QblJsonMainConfigContact *contact);
    /**
     * Get chat history
     * @param contact Contact
     * @return chat history
     */
    std::list<QblJsonChatMessageComplete> getHistory(
            QblJsonMainConfigContact *contact);

protected:
    IQblChatReceive *listener; /**< Listener which listen to the
     received chat messages */
    /** Contact for which want the history */
    std::list<QblJsonMainConfigContact *> contactListener;

    /**
     * Create chat history and send it to the client
     * @param contact Contact for which the history list shall created
     * @return chat history
     */
    std::list<QblJsonChatMessageComplete> getHistoryList(
            std::string contact);

private:
};

#endif /* __QBL_CHAT_HISTORY_H__ */
