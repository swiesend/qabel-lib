/**
 * @file		messages.cpp
 * @brief		Example for system tray messages
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

#include <list>
using namespace std;

#include <stdio.h>

#include "qbl.h"
#include "qbl-message.h"
#include "qbl-messages.h"
#include "iqbl-messages.h"

class Messages: public IQblMessages {
public:
    Messages()
    {
        messages = new QblMessages();
        messages->addListener(this);

        return;
    }

    ~Messages()
    {

    }

    void setMessages(QblMessage::contentType header)
    {
        std::string msg;
        messages->addMessage(std::time(NULL), QblMessage::INFO, header);

        return;
    }

    void getMessages()
    {
        std::list<QblMessage> list;
        std::list<QblMessage>::iterator iterator;

        list = messages->getAllMessages();
        list.empty();

        return;
    }

    void getMessages(int count)
    {
        std::list<QblMessage> list;
        std::list<QblMessage>::iterator iterator;

        list = messages->getMessages(count);
        list.empty();

        return;
    }

private:
    QblMessages *messages;

    void newMessageReceived(QblMessage *message)
    {

    }

};

int main(void)
{
    Messages *messages;
    int i;

    messages = new Messages();
    for (i = 0; i < 10; i++) {
        messages->setMessages(QblMessage::CHAT);
        messages->setMessages(QblMessage::UPLOAD_NEW_VERSION);

        messages->getMessages(8);
    }

    messages->getMessages();

    delete (messages);

    return 0;
}
