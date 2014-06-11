/**
 * @file		qbl-message.h
 * @brief		Class to handle a message (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_MESSAGE_H__
#define __QBL_MESSAGE_H__

#include <string>
#include <ctime>
using namespace std;

#include "qbl-json-chat.h"

/**
 * QblMessage: Class which handle a message
 */
class QblMessage {
public:
    /**
     * Type of the message
     */
    enum type {
        INFO,                       /**< INFO: This message will inform the
                                      client, default value */
        WARN,                       /**< WARN: The message will warn the
                                      client */
        ERROR,                      /**< ERROR: The is an error in the
                                      communication */
        DO,                         /**< DO: The client have to do an action */
    };
    /**
     * Content type of the message based on the QblJsonChat::type
     */
    enum contentType {
        NO_ID = 0x0000,             /**< No id is set */
        /* chat; starting with 0x00 */
        CHAT = 0x0100,              /**< Normal chat message */
        CHAT_RECEIVED = 0x0200,     /**< Other side received message */
        CHAT_READED = 0x0300,       /**< Other side read message */
        CHAT_KNOCKING = 0x0400,     /**< Other side is knocking */
        /* group chat; starting with 0x10 */
        /* micro blog; starting with 0x20 */
        /* chat: file sended; starting with 0x30 */
        CHAT_FILE_NEW = 0x1000,     /**< Other side wants to send a file */
        CHAT_FILE_ACCEPTED = 0x1100,/**< Other side accept file or not */
        CHAT_FILE_RECEIVED = 0x1200,/**< Other side received the file ->
                                      delete from storage */
        /* contact; starting with 0x40 */
        CONTACT = 0x4000,           /**< Received a new contact request */
        CONTACT_IMAGE = 0x4100,     /**< Contact send its image */
        /* file upload / sync; starting with 0x50 */
        UPLOAD = 0x5000,            /**!< */
        UPLOAD_LINK = 0x5100,       /**!< Share upload link with other */
        UPLOAD_LINK_ACCEPTED = 0x5200, /*!< Other side is accepted share upload
                                         link */
        UPLOAD_NEW_VERSION = 0x5300, /**!< Uploaded archive is changed */
        UPLOAD_NEW_VERSION_MAC = 0x5400, /**!< Uploaded archive is changed. This
                                           message is for the uploader that its
                                           other devices now that archive is
                                           updated */
        UPLOAD_LINK_REMOVED = 0x5500, /**!< Other is not longer allowed to see
                                       data */
        UPLOAD_REMOVED = 0x5600,    /**!< Uploaded archive is deleted */
    };
    /**
     * Constructor
     */
    QblMessage();
    /**
     * Constructor
     * @param timestamp Time stamp of the message
     * @param type Type of the message
     * @param contentType Content type
     */
    QblMessage(std::time_t timestamp, QblMessage::type type,
            contentType contentType);
    /**
     * Constructor
     * @param timestamp Time stamp of the message
     * @param type Type of the message
     * @param contentType Content type
     * @param chat Chat message to handle
     */
    QblMessage(std::time_t timestamp, QblMessage::type type,
            contentType contentType, QblJsonChat chat);
    /**
     * Destructor
     */
    virtual ~QblMessage();

    /**
     * Get the time stamp of the message
     * @return Time stamp
     */
    std::time_t getTimestamp() const;
    /**
     * Set the time stamp of the message
     * @param timestamp New time stamp
     */
    void setTimestamp(std::time_t timestamp);
    /**
     * Get type of the message
     * @return Message Type
     */
    QblMessage::type getType() const;
    /**
     * Set type of the message
     * @param type Message Type
     */
    void setType(QblMessage::type type);
    /**
     * Get content type of the message
     * @return Message content type
     */
    contentType getContentType() const;
    /**
     * Set content type of the message
     * @param contentType Message content type
     */
    void setContentType(contentType contentType);
    const QblJsonChat& getChat() const;
    void setChat(const QblJsonChat& chat);

private:
    std::time_t timestamp;          /**< Time stamp */
    QblMessage::type _type;         /**< Message type */
    QblMessage::contentType _contentType; /**< Message content type */
    QblJsonChat chat;               //!< Chat message to handle
};

#endif                          /* __QBL_MESSAGE_H__ */
