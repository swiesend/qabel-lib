/*
 * @file		qbl-chat-history-internal.h
 * @brief		Internal library class to handle chat history (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CHAT_HISTORY_INTERNAL_H__
#define __QBL_CHAT_HISTORY_INTERNAL_H__

#include <map>
using namespace std;

#include "qbl-chat-history.h"
#include "qbl-json-chat.h"
#include "qbl-json-main-config.h"

class QblJsonChat;
class QblJsonChat;
class QblJsonMainConfigContact;

typedef std::pair<std::string, QblJsonChat> QblChatHistoryPair;
/**
 * Class QblChatHistoryInternal: Internal library class to handle chat history
 */
class QblChatHistoryInternal: public QblChatHistory {
public:
    /**
     * Constructor
     */
    QblChatHistoryInternal();
    /**
     * Destructor
     */
    virtual ~QblChatHistoryInternal();

    /**
     * add message to history queue
     * @param chat Send message
     * @param contactAlias Contact alias
     */
    void addMessage(std::string contactAlias, QblJsonChat chat);
    /**
     * handle message queue
     * @todo Split history in more than one file
     * @todo Forward error message to message queue
     */
    void handleMessage();

private:
    std::list<QblChatHistoryPair> list;
    std::mutex listMutex;

    /**
     * Save chat message to history
     * @param contact Contact for which the history shall saved
     * @param jsonStr JSON string to save
     */
    void saveMessageToHistory(std::string contact, std::string jsonStr);
    /**
     * Create chat history and send it to the client
     * @param contact Contact for which the history list shall created
     */
    void createHistoryList(std::string contact);
};

#endif /* __QBL_CHAT_HISTORY_INTERNAL_H__ */
