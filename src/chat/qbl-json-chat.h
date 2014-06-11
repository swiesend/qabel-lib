/*
 * @file		qbl-json-chat.h
 * @brief		Class to handle a chat message (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_H__
#define __QBL_JSON_CHAT_H__

#include <string>
using namespace std;

#include "qbl-json.h"

/**
 * class QblJsonChat: Class to handle chat message
 */
class QblJsonChat: public QblJson {
public:
    /**
     * Message type
     */
    enum messageType {
        NO_TYPE = 0x00,             /**< No type is set */
        /* chat; starting with 0x00 */
        CHAT = 0x01,                /**< Normal chat message */
        CHAT_RECEIVED = 0x02,       /**< Other side received message */
        CHAT_READED = 0x03,         /**< Other side read message */
        CHAT_KNOCKING = 0x04,       /**< Other side is knocking */
        /* group chat; starting with 0x10 */
        /* micro blog; starting with 0x20 */
        /* chat: file sended; starting with 0x30 */
        CHAT_FILE_NEW = 0x10,       /**< Other side wants to send a file */
        CHAT_FILE_ACCEPTED = 0x11,  /**< Other side accept file or not */
        CHAT_FILE_RECEIVED = 0x12,  /**< Other side received the file ->
                                      delete from storage */
        /* contact; starting with 0x40 */
        CONTACT = 0x40,             /**< Received a new contact request */
        CONTACT_IMAGE = 0x41,       /**< Contact send its image */
        /* file upload / sync; starting with 0x50 */
        UPLOAD = 0x50,              /**!< */
        UPLOAD_LINK = 0x51,         /**!< Share upload link with other */
        UPLOAD_LINK_ACCEPTED = 0x52,/**!< Other side is accepted share upload
                                      link */
        UPLOAD_NEW_VERSION = 0x53,  /**!< Uploaded archive is changed */
        UPLOAD_NEW_VERSION_MAC = 0x54,  /**!< Uploaded archive is changed. This
                                          message is for the uploader that its
                                          other devices now that archive is
                                          updated */
        UPLOAD_LINK_REMOVED = 0x55,  /**!< Other is not longer allowed to see
                                       data */
        UPLOAD_REMOVED = 0x56,      /**!< Uploaded archive is deleted */
    };
	/**
	 * Constructor for paring a JSON object
	 */
    QblJsonChat();
	/**
	 * Constructor for paring a JSON object
	 * @param jsonString JSON string to parse
	 */
    QblJsonChat(std::string jsonString);
    /**
     * Constructor to create a nearly empty chat JSON object
	 * @param sender Sender of the message
     * @param type Message type
     */
    QblJsonChat(std::string sender, messageType type);
    /**
     * Constructor
	 * @param sender Sender of the message
     * @param fileName Name of the file
     * @param key Key to encrypt the file
     */
    QblJsonChat(std::string sender, std::string fileName, std::string key);
    /**
     * Constructor
     * @param obj Object to parse
     */
    QblJsonChat(json_object *obj);
    /**
     * Destructor
     */
    virtual ~QblJsonChat();

    /**
     * Function to parse the JSON string
     * @return true == everything okay
     */
    void parse(std::string string);
    /**
     * Function to parse the JSON object
     * @param obj Object to parse
     * @return
     */
    void parse(json_object *obj = NULL);
    /**
     * Function to parse a part of the JSON object
     * @param key Key
     * @param value Value
     * @return true if something is found
     */
    bool parse(char *key, json_object *value);
    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    void integrate(QblJson *other);

    /**
     * Get current sender
     * @return Current sender
     */
    const std::string& getSender() const;
    /**
     * Get the type of the message
     * @return Message type
     */
    messageType getType() const;
    /**
     * Get current message
     * @return Current message
     */
    const std::string& getMessage() const;
    bool isYesNo() const;
    /**
     * Get current key
     * @return Current key
     */
    const std::string& getKey() const;
    /**
     * Get current file
     * @return Current file
     */
    const std::string& getFile() const;
    /**
     * Get current file name
     * @return Current file name
     */
    const std::string& getFileName() const;
    const std::string& getServer() const;
    int getPort() const;
    const std::string& getPath() const;
    const std::string& getPublic() const;
    int getUuidToSend() const;
    int64_t getMac() const;
    /**
     * Get current message
     * @return Current message
     */
    const bool& isMessageSend() const;
    /**
     * Set whether message is send
     * @param state Send state
     */
    void setSendState(const bool& state);

protected:
    enum elementType {
       SENDER = 0,
       MESSAGE_TYPE = 1,
       MESSAGE = 2,
       MESSAGE_DATE = 3,
       SEND = 4,
       YES_NO = 5,
       KEY = 6,
       FILE_NAME = 7,
       FILE = 8,
       SERVER = 9,
       PORT = 10,
       PATH = 11,
       PUBLIC = 12,
       UUID_TO_SEND = 13,
       MAC = 14,
    };
    struct element elements[15] = {
        /** Who send the message */
        { "sender", json_type_string, new std::string(), false, true, true },
        /** Message type */
        { "message_type", json_type_int, new int(), false, true, true },
        /** Message to send */
        { "message", json_type_string, new std::string(), false, false, true },
        /** Message date */
        { "message_date", json_type_int, new time_t(), false, false, true },
        /** Is message sended; only internal */
        { "send", json_type_boolean, new bool(), false, false, true },
        /** boolean value for different messages types */
        { "yes_no", json_type_boolean, new bool(), false, false, true },
        /** key of the file */
        { "key", json_type_string, new std::string(), false, false, true },
        /** file name */
        { "file_name", json_type_string, new std::string(), false, false,
                true },
        /** file */
        { "file", json_type_string, new std::string(), false, false, true },
        /** block_server name */
        { "server", json_type_string, new std::string(), false, false, true },
        /** block_server port */
        { "port", json_type_int, new int(), false, false, true },
        /** block_server path */
        { "path", json_type_string, new std::string(), false, false, true },
        /** public */
        { "public", json_type_string, new std::string(), false, false, true },
        { "uuid_to_send", json_type_int, new int(), false, false, true },
        { "mac", json_type_int, new int64_t(), false, false, true },
    };

    /**
     * Set new sender
     * @param sender New sender
     */
    void setSender(const std::string& sender);
    /**
     * Set new message type
     * @param type New message type
     */
    void setType(messageType type);
    /**
     * Set new message
     * @param message New message
     */
    void setMessage(const std::string& message);
    void setYesNo(bool yesNo);
    /**
     * Set new key
     * @param key New key
     */
    void setKey(const std::string& key);
    /**
     * Set new file
     * @param file New file
     */
    void setFile(const std::string& file);
    /**
     * Set new file name
     * @param file_name New file name
     */
    void setFileName(const std::string& fileName);
    void setServer(const std::string& blockServer);
    void setPort(int port);
    void setPath(const std::string& path);
    void setPublic(const std::string& _public);
    void setUuidToSend(int uuidToSend);
    void setMac();

};

#endif /* __QBL_JSON_CHAT_H__ */
