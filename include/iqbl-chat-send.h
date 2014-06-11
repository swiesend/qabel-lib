/*
 * @file		iqbl-chat-send.h
 * @brief		Class to handle callbacks from sended messages (Header file)
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

#ifndef __IQBL_CHAT_SEND_H__
#define __IQBL_CHAT_SEND_H__

/**
 * IQblChatSend: Class to handle callbacks from sended messages
 *
 */
class IQblChatSend {
public:
    /**
     * Constructor
     */
    IQblChatSend()
    {

        return;
    }
    /**
     * Destructor
     */
    virtual ~IQblChatSend()
    {

        return;
    }

    /**
     * Callback function to receive the last message add the the message list
     * @param message Last message
     */
    virtual void messageSend(bool done) = 0;

};

#endif                          /* __IQBL_CHAT_SEND_H__ */
