/**
 * @file		qbl.cpp
 * @brief		Example for Qabel main library
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

#include <cstdio>
#include <cstdlib>

#include <qbl.h>
#include <qbl-json-main-config-identity.h>
#include <qbl-json-main-config-identity-array.h>
#include <qbl-main-config.h>
#include <qbl-message.h>
#include <qbl-messages.h>

class QblExample: public IQbl {
public:
    QblExample()
    {
        std::list<QblJsonMainConfigIdentity *> identities;
        std::list<QblJsonMainConfigIdentity *>::iterator id_it;

        this->qbl = Qbl::getInstance();
        if (this->qbl == NULL) {
            exit(EXIT_FAILURE);
        }
        this->qbl->addListener(this);

        // List config
        identities = this->qbl->getConfig()->getIdentities()->getList();
        for (id_it = identities.begin(); id_it != identities.end(); id_it++) {

        }
        return;
    }

    ~QblExample()
    {

    }

    void setMessages(string header)
    {
        std::string msg;

        this->qbl->getSystemTrayMessages()->addMessage(std::time(NULL),
                QblMessage::INFO, QblMessage::CHAT);

        return;
    }

    void getMessages()
    {
        std::list<QblMessage> list;
        std::list<QblMessage>::iterator iterator;

        list = this->qbl->getSystemTrayMessages()->getAllMessages();
        list.empty();

        return;
    }

    void getMessages(int count)
    {
        std::list<QblMessage> list;
        std::list<QblMessage>::iterator iterator;

        list = this->qbl->getSystemTrayMessages()->getMessages(count);
        list.empty();

        return;
    }

private:
    Qbl *qbl;

    void newMessageReceived(QblMessage *message)
    {

    }

};

int main(void)
{
    QblExample *qbl;
    int i;

    qbl = new QblExample();

    delete (qbl);

    return 0;
}
