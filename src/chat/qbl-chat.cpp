/*
 * @file		qbl-chat.cpp
 * @brief		Main library class for the chat (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <cstdio>
#include <list>

#include "qbl-chat.h"
#include "qbl-json-main-config-identity-array.h"
#include "qbl.h"
#include "qbl-main-config.h"
#include "qbl-chat-message-receive.h"

QblChat::QblChat()
{
    this->configUpdated();

    return;
}

QblChat::~QblChat()
{

    return;
}

void QblChat::configUpdated()
{
    // TODO add error handling
    Qbl *qbl;
    qbl = Qbl::getInstance();

    this->identities = qbl->getConfig()->getIdentities()->getList();
    this->current = this->identities.end();

    return;
}

void QblChat::checkNextIdentity()
{
    

    if (this->identities.size() == 0) {
        return;
    }

    if (this->current == this->identities.end()) {
        this->current = this->identities.begin();
    } else {
        this->current++;
        if (this->current == this->identities.end()) {
            this->current = this->identities.begin();
        }
    }

    QblChatMessageReceive obj(*this->current);
    /*bool retval =*/ obj.sendMessage();

    // TODO: error handling

    return;
}
