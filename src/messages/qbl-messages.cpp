/**
 * @file		qbl-messages.cpp
 * @brief		Class to handle messages (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <list>

#include "qbl-message.h"
#include "qbl-messages.h"

#define LIST_LENGTH 10

QblMessages::QblMessages() :
        listLength(LIST_LENGTH)
{

    return;
}

QblMessages::~QblMessages()
{
    std::list<IQblMessages *>::iterator iterator;

    messages.empty();

    for (iterator = listeners.begin(); iterator != listeners.end();
            iterator++) {
        delete (*iterator);
    }
    listeners.empty();

    return;
}

void QblMessages::addMessage(QblMessage message)
{
    std::list<IQblMessages *>::iterator iterator;

    if (messages.size() == listLength) {
        messages.pop_front();
    }

    messages.push_back(message);

    for (iterator = listeners.begin(); iterator != listeners.end();
            iterator++) {
        (*iterator)->newMessageReceived(&message);
    }

    return;
}

void QblMessages::addMessage(std::time_t timestamp, QblMessage::type type,
        QblMessage::contentType contentType)
{
    QblMessage message;

    message = QblMessage(timestamp, type, contentType);
    this->addMessage(message);

    return;
}

QblMessage QblMessages::getLastMessage()
{
    int length;
    QblMessage result;
    std::list<QblMessage>::iterator iterator;

    length = messages.size();
    if (length != 0) {
        result = messages.back();
    }

    return (result);
}

std::list<QblMessage> QblMessages::getMessages(int count)
{
    std::list<QblMessage> result;
    int length = messages.size();
    std::list<QblMessage>::iterator iterator;

    iterator = messages.begin();
    if (length > count) {
        for (; iterator != messages.end(); iterator++) {
            length--;
            if (length < count) {
                break;
            }
            continue;
        }
    }

    for (; iterator != messages.end(); iterator++) {
        result.push_back(*iterator);
    }

    return (result);
}

std::list<QblMessage> QblMessages::getAllMessages()
{
    std::list<QblMessage> result;
    std::list<QblMessage>::iterator iterator;

    for (iterator = messages.begin(); iterator != messages.end(); iterator++) {
        result.push_back(*iterator);
    }

    return (result);
}

int QblMessages::getListLength() const
{
    return (listLength);
}

void QblMessages::setListLength(int listLength)
{
    if (listLength < 1) {
        return;
    }
    this->listLength = listLength;

    return;
}

void QblMessages::addListener(IQblMessages *listener)
{
    listeners.push_back(listener);

    return;
}

void QblMessages::removeListener(IQblMessages *listener)
{
    std::list<IQblMessages *>::iterator iterator;

    for (iterator = listeners.begin(); iterator != listeners.end();
            iterator++) {
        if (*iterator == listener) {
            listeners.erase(iterator);
        }
    }

    return;
}
