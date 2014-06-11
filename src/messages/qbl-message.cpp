/**
 * @file		qbl-message.cpp
 * @brief		Class to handle a message (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-message.h"

QblMessage::QblMessage()
{

    return;
}

QblMessage::QblMessage(std::time_t timestamp, QblMessage::type type,
        QblMessage::contentType contentType) :
    timestamp(timestamp), _type(type), _contentType(contentType)
{
    return;
}

QblMessage::QblMessage(std::time_t timestamp, QblMessage::type type,
        contentType contentType, QblJsonChat chat) :
    timestamp(timestamp), _type(type), _contentType(contentType), chat(chat)
{
    return;
}

QblMessage::~QblMessage()
{
    // TODO Auto-generated destructor stub
}

std::time_t QblMessage::getTimestamp() const
{
    return (this->timestamp);
}

void QblMessage::setTimestamp(std::time_t timestamp)
{
    this->timestamp = timestamp;

    return;
}

QblMessage::contentType QblMessage::getContentType() const
{
    return (this->_contentType);
}

void QblMessage::setContentType(QblMessage::contentType contentType)
{
    this->_contentType = contentType;

    return;
}

QblMessage::type QblMessage::getType() const
{
    return (this->_type);
}

void QblMessage::setType(QblMessage::type type)
{
    this->_type = type;

    return;
}

const QblJsonChat& QblMessage::getChat() const
{
    return (this->chat);
}

void QblMessage::setChat(const QblJsonChat& chat)
{
    this->chat = chat;

    return;
}
