/*
 * @file		iqbl-chat-receive.h
 * @brief		Class to handle callbacks from received messages (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * copyright:	(C) 2014 by Qabel GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __IQBL_CHAT_RECEIVE_H__
#define __IQBL_CHAT_RECEIVE_H__

#include "qbl-json-chat-message-complete.h"

/**
 * IQblChatReceive: Class to handle callbacks from chat
 *
 */
class IQblChatReceive {
public:
    /**
     * Constructor
     */
    IQblChatReceive()
    {

        return;
    }
    /**
     * Destructor
     */
    virtual ~IQblChatReceive()
    {

        return;
    }

    /**
     * Callback function to receive the last message add the the message list
     * @param contact Contact alias which send the message
     * @param lastMessages List of last messages
     */
    virtual void messageReceived(std::string contact,
            QblJsonChatMessageCompleteList lastMessages) = 0;

};

#endif                          /* __IQBL_CHAT_RECEIVE_H__ */
