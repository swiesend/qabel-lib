/*
 * @file		qbl-chat.h
 * @brief		Main library class for the chat (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CHAT_H__
#define __QBL_CHAT_H__

#include "iqbl-chat-receive.h"

#include "qbl-json-chat.h"
#include "qbl-json-main-config-identity.h"

class QblChat {
public:
    /**
     * Constructor
     */
    QblChat();
    /**
     * Destructor
     */
    virtual ~QblChat();

    /**
     * Function which shall called when the configuration of the identities
     * is changed
     */
    void configUpdated();
    /**
     * Get next identity and check for new messages
     * @todo Add error handling
     */
    void checkNextIdentity();

private:
    std::list<QblJsonMainConfigIdentity *> identities;
    std::list<QblJsonMainConfigIdentity *>::iterator current;


};

#endif /* __QBL_CHAT_H__ */
