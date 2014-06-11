/*
 * @file		qbl.h
 * @brief		Main Class the Qabel library (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_H__
#define __QBL_H__

#include <ctime>
#include <exception>
#include <initializer_list>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include "iqbl.h"
#include "iqbl-messages.h"
#include "qbl-messages.h"
#include "qbl-object.h"
#include "qbl-main-config.h"
#include "qbl-chat-history.h"
#include "qbl-fs.h"
#include "qbl-net-mac.h"

class IQblChatReceive;
class QblChat;
class QblFs;

typedef std::list<QblFs *> QblFsList;

/**
 * Class QblException: Standard exception for the library
 */
class QblException: public exception {
public:
    /**
     * Constructor
     * @param list Messages to send
     */
    QblException(std::initializer_list<std::string> list)
    {
        what(list);
    }
    /**
     * What was the problem
     * @return Error description
     */
    const std::string what(
            const std::initializer_list<std::string> list) const throw ()
    {
        std::string msg;

        for (std::string elem : list) {
            msg += elem;
        }
        return (msg);
    }

};

/**
 * Qbl: Main Class the Qabel library
 */
class Qbl: public IQblMessages {
public:
    /**
     * Destructor
     */
    virtual ~Qbl();

    /**
     * Get a singleton of the main class
     * @return Singleton object or NULL on error
     */
    static Qbl *getInstance();

    /**
     * Get a singleton of the main class and add the listener to Qbl
     * @param listener Listener to add
     * @return Singleton object
     */
    static Qbl *getInstance(IQbl * listener);

    /**
     * Add listener to Qbl
     * @param listener Listener to add
     */
    void addListener(IQbl * listener);

    /**
     * Remove listener from Qbl
     * @param listener Listener to remove
     */
    void removeListener(IQbl * listener);

    /**
     * Main thread handling function
     */
    void runMainThread();
    /**
     * Get the object which handle the system tray
     * @return QblMessages object
     */
    QblMessages *&getSystemTrayMessages();
    /**
     * Get the main configuration of the application
     * @return Configuration or NULL if no configuration is available
     */
    QblMainConfig *&getConfig();
    /**
     * Add message to the send message queue
     * @param object Message to send
     */
    void addMessageToQueue(QblObject *object);
    /**
     * Add listener which handle the received message
     * @param chatReceiveListener Listener object
     */
    void setChatReceiveListener(IQblChatReceive* chatReceiveListener);
    /**
     * Get reference to the chat history object
     * @return References to chat history
     */
    QblChatHistory*& getChatHistory();
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    static bool strp_atoi(const char * & s, int & result, int low, int high,
            int offset);
    /**
     * Reimplementation of strptime
     * @param s Buffer in which time stamp has to add
     * @param format Format of the string
     * @param tm Time stamp
     * @return
     */
    static char *strptime(const char *s, const char *format, struct tm *tm);
#endif

    /**
     * Get object which collect some network information
     * @return QblNetMac object
     */
    QblNetMac*& getMac();

protected:
    /**
     * Constructor
     */
    Qbl();

private:
    std::thread mainThread;         /**< Main thread */
    bool mainThreadRunning;         /**< Identify whether the main thread is
                                      running */
    QblMessages *systemTrayMessages; /**< Object to handle system tray
                                       messages */
    std::list<IQbl *> listeners;    /**< Listener list which want to receive
                                      callbacks */
    QblMainConfig *config;          /**< Default configuration */
    std::list<QblObject *> sendingObject; /**< Object to send to recipient */
    std::mutex sendingObjectMutex;  /**< Mutex for sending object list */

    QblChat *chat;
    QblChatHistory *chatHistory;    /**< Chat history object */

    QblFsList fs;                   //!< QblFs object
    QblFsList::iterator currentFs;  //!< current checked directory

    time_t timestamp;

    QblNetMac *mac;                 //!< Some information about the network

    /**
     * Initialise the library during start
     * @return 0 == ok
     */
    int initLibrary();
    /**
     * Handle the callback from system tray messages and forward it to caller
     * @param message Received message
     */
    void newMessageReceived(QblMessage *message);
    /**
     * Check next directory in list
     */
    void checkNextFs();
};

#endif                          /* __QBL_H__ */
