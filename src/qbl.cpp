/*
 * @file		qbl.cpp
 * @brief		Main Class the Qabel library (Implementation)
 * @brief		Class to handle callback for the system tray (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <chrono>
#include <cstdio>
#include <system_error>
#include <string.h>

#include "qbl.h"
#include "qbl-chat.h"
#include "qbl-chat-history-internal.h"
#include "qbl-chat-message-send.h"
#include "qbl-config-file.h"
#include "qbl-message.h"
#include "qbl-messages.h"
#include "qbl-main-config.h"
#include "qbl-json-main-config-share-array.h"
#include "qbl-block-upload.h"

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
const char *strp_weekdays[] = {
    "sunday", "monday", "tuesday", "wednesday", "thursday", "friday",
    "saturday"
};

const char *strp_monthnames[] = {
    "january", "february", "march", "april", "may", "june", "july",
        "august",
    "september", "october", "november", "december"
};
#endif

static Qbl *qbl = NULL;

Qbl::~Qbl()
{
    this->systemTrayMessages->removeListener(this);

    this->mainThreadRunning = false;
    try {
        mainThread.join();
    } catch(const std::system_error & exception) {
    }

    this->listeners.clear();

    return;
}

Qbl *Qbl::getInstance()
{
    if (qbl == NULL) {
        int retval;

        srandom(time(NULL));

        qbl = new Qbl();
        retval = qbl->initLibrary();
        if (retval != 0) {
            delete(qbl);
            qbl = NULL;
        }
    }

    return (qbl);
}

Qbl *Qbl::getInstance(IQbl * listener)
{
    getInstance();

    qbl->addListener(listener);

    return (qbl);
}

void Qbl::addListener(IQbl * listener)
{
    listeners.push_back(listener);

    return;
}

void Qbl::removeListener(IQbl * listener)
{
    std::list < IQbl * >::iterator iterator;

    for (iterator = listeners.begin(); iterator != listeners.end();
         iterator++) {
        //IQbl *buffer = *iterator;
        if (*iterator == listener) {
            listeners.erase(iterator);
        }
    }

    return;
}

void Qbl::runMainThread()
{
    bool retval;
    this->mainThreadRunning = true;
    time_t now;

    while (this->mainThreadRunning == true) {

        // send saved object in list
        if (this->sendingObject.size() > 0) {
            std::list < QblObject * >::iterator iterator;
            bool toDelete;

            this->sendingObjectMutex.lock();
            for (iterator = this->sendingObject.begin();
                 iterator != this->sendingObject.end();) {
                toDelete = false;

                if ((*iterator)->getType() == QblObject::CHAT) {
                    retval =
                        ((QblChatMessageSend *) (*iterator))->
                        sendMessage();
                    if (retval == true) {
                        toDelete = true;
                    }
                } else {

                }

                // Deleting elements
                if (toDelete == true) {
                    delete(*iterator);
                    this->sendingObject.erase(iterator++);
                } else {
                    iterator++;
                }
            }
            this->sendingObjectMutex.unlock();
        }

        // Handle chat history
        ((QblChatHistoryInternal *) this->getChatHistory())->
            handleMessage();

        now = time(NULL);
        if (this->timestamp != now) {
            this->timestamp = now;

            // Check next identity for chat messages
            if (this->chat != NULL) {
                this->chat->checkNextIdentity();

                // File system check
                this->checkNextFs();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return;
}

QblMessages *&Qbl::getSystemTrayMessages()
{
    return (this->systemTrayMessages);
}

QblMainConfig *&Qbl::getConfig()
{
    return (this->config);
}

void Qbl::addMessageToQueue(QblObject * object)
{
    this->sendingObjectMutex.lock();
    this->sendingObject.push_back(object);
    this->sendingObjectMutex.unlock();

    return;
}

void Qbl::setChatReceiveListener(IQblChatReceive * chatReceiveListener)
{
    if (this->chat == NULL) {
        this->chat = new QblChat();
    }

    this->chatHistory->addListener(chatReceiveListener);

    return;
}

QblChatHistory *&Qbl::getChatHistory()
{
    return (this->chatHistory);
}

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
bool Qbl::strp_atoi(const char *&s, int &result, int low, int high,
                    int offset)
{
    bool worked = false;
    char *end;
    unsigned long num = strtoul(s, &end, 10);
    if (num >= (unsigned long) low && num <= (unsigned long) high) {
        result = (int) (num + offset);
        s = end;
        worked = true;
    }
    return worked;
}

char *Qbl::strptime(const char *s, const char *format, struct tm *tm)
{
    bool working = true;

    while (working && *format && *s) {
        switch (*format) {
        case '%':
            {
                ++format;
                switch (*format) {
                case 'a':
                case 'A':      // weekday name
                    tm->tm_wday = -1;
                    working = false;
                    for (size_t i = 0; i < 7; ++i) {
                        size_t len = strlen(strp_weekdays[i]);
                        if (!strnicmp(strp_weekdays[i], s, len)) {
                            tm->tm_wday = i;
                            s += len;
                            working = true;
                            break;
                        } else if (!strnicmp(strp_weekdays[i], s, 3)) {
                            tm->tm_wday = i;
                            s += 3;
                            working = true;
                            break;
                        }
                    }
                    break;
                case 'b':
                case 'B':
                case 'h':      // month name
                    tm->tm_mon = -1;
                    working = false;
                    for (size_t i = 0; i < 12; ++i) {
                        size_t len = strlen(strp_monthnames[i]);
                        if (!strnicmp(strp_monthnames[i], s, len)) {
                            tm->tm_mon = i;
                            s += len;
                            working = true;
                            break;
                        } else if (!strnicmp(strp_monthnames[i], s, 3)) {
                            tm->tm_mon = i;
                            s += 3;
                            working = true;
                            break;
                        }
                    }
                    break;
                case 'd':
                case 'e':      // day of month number
                    working = strp_atoi(s, tm->tm_mday, 1, 31, -1);
                    break;
                case 'D':      // %m/%d/%y
                    {
                        const char *s_save = s;
                        working = strp_atoi(s, tm->tm_mon, 1, 12, -1);
                        if (working && *s == '/') {
                            ++s;
                            working = strp_atoi(s, tm->tm_mday, 1, 31, -1);
                            if (working && *s == '/') {
                                ++s;
                                working =
                                    strp_atoi(s, tm->tm_year, 0, 99, 0);
                                if (working && tm->tm_year < 69)
                                    tm->tm_year += 100;
                            }
                        }
                        if (!working)
                            s = s_save;
                    }
                    break;
                case 'H':      // hour
                    working = strp_atoi(s, tm->tm_hour, 0, 23, 0);
                    break;
                case 'I':      // hour 12-hour clock
                    working = strp_atoi(s, tm->tm_hour, 1, 12, 0);
                    break;
                case 'j':      // day number of year
                    working = strp_atoi(s, tm->tm_yday, 1, 366, -1);
                    break;
                case 'm':      // month number
                    working = strp_atoi(s, tm->tm_mon, 1, 12, -1);
                    break;
                case 'M':      // minute
                    working = strp_atoi(s, tm->tm_min, 0, 59, 0);
                    break;
                case 'n':      // arbitrary whitespace
                case 't':
                    while (isspace((int) *s))
                        ++s;
                    break;
                case 'p':      // am / pm
                    if (!strnicmp(s, "am", 2)) {    // the hour will be 1 -> 12 maps to 12 am, 1 am .. 11 am, 12 noon 12 pm .. 11 pm
                        if (tm->tm_hour == 12)  // 12 am == 00 hours
                            tm->tm_hour = 0;
                    } else if (!strnicmp(s, "pm", 2)) {
                        if (tm->tm_hour < 12)   // 12 pm == 12 hours
                            tm->tm_hour += 12;  // 1 pm -> 13 hours, 11 pm -> 23 hours
                    } else
                        working = false;
                    break;
                case 'r':      // 12 hour clock %I:%M:%S %p
                    {
                        const char *s_save = s;
                        working = strp_atoi(s, tm->tm_hour, 1, 12, 0);
                        if (working && *s == ':') {
                            ++s;
                            working = strp_atoi(s, tm->tm_min, 0, 59, 0);
                            if (working && *s == ':') {
                                ++s;
                                working =
                                    strp_atoi(s, tm->tm_sec, 0, 60, 0);
                                if (working && isspace((int) *s)) {
                                    ++s;
                                    while (isspace((int) *s))
                                        ++s;
                                    if (!strnicmp(s, "am", 2)) {    // the hour will be 1 -> 12 maps to 12 am, 1 am .. 11 am, 12 noon 12 pm .. 11 pm
                                        if (tm->tm_hour == 12)  // 12 am == 00 hours
                                            tm->tm_hour = 0;
                                    } else if (!strnicmp(s, "pm", 2)) {
                                        if (tm->tm_hour < 12)   // 12 pm == 12 hours
                                            tm->tm_hour += 12;  // 1 pm -> 13 hours, 11 pm -> 23 hours
                                    } else
                                        working = false;
                                }
                            }
                        }
                        if (!working)
                            s = s_save;
                    }
                    break;
                case 'R':      // %H:%M
                    {
                        const char *s_save = s;
                        working = strp_atoi(s, tm->tm_hour, 0, 23, 0);
                        if (working && *s == ':') {
                            ++s;
                            working = strp_atoi(s, tm->tm_min, 0, 59, 0);
                        }
                        if (!working)
                            s = s_save;
                    }
                    break;
                case 'S':      // seconds
                    working = strp_atoi(s, tm->tm_sec, 0, 60, 0);
                    break;
                case 'T':      // %H:%M:%S
                    {
                        const char *s_save = s;
                        working = strp_atoi(s, tm->tm_hour, 0, 23, 0);
                        if (working && *s == ':') {
                            ++s;
                            working = strp_atoi(s, tm->tm_min, 0, 59, 0);
                            if (working && *s == ':') {
                                ++s;
                                working =
                                    strp_atoi(s, tm->tm_sec, 0, 60, 0);
                            }
                        }
                        if (!working)
                            s = s_save;
                    }
                    break;
                case 'w':      // weekday number 0->6 sunday->saturday
                    working = strp_atoi(s, tm->tm_wday, 0, 6, 0);
                    break;
                case 'Y':      // year
                    working =
                        strp_atoi(s, tm->tm_year, 1900, 65535, -1900);
                    break;
                case 'y':      // 2-digit year
                    working = strp_atoi(s, tm->tm_year, 0, 99, 0);
                    if (working && tm->tm_year < 69)
                        tm->tm_year += 100;
                    break;
                case '%':      // escaped
                    if (*s != '%')
                        working = false;
                    ++s;
                    break;
                default:
                    working = false;
                }
            }
            break;
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '\f':
        case '\v':
            // zero or more whitespaces:
            while (isspace((int) *s))
                ++s;
            break;
        default:
            // match character
            if (*s != *format)
                working = false;
            else
                ++s;
            break;
        }
        ++format;
    }
    return (working ? (char *) s : 0);
}
#endif

QblNetMac*& Qbl::getMac()
{
    return (this->mac);
}

Qbl::Qbl():
config(NULL), chat(NULL), chatHistory(NULL), timestamp(0), mac(NULL)
{
    return;
}

int Qbl::initLibrary()
{
    int retval;
    QblConfigFile *file;
    QblJsonMainConfigShareList shares;
    QblJsonMainConfigShareList::iterator shareIt;

    // read configuration
    file = new QblConfigFile();
    retval = file->readConfigFile(&this->config);
    if (retval != 0) {
        return (retval);
    }
    // initialise the system tray message list
    this->systemTrayMessages = new QblMessages();
    this->systemTrayMessages->addListener(this);

    // Using the internal class
    this->chatHistory = new QblChatHistoryInternal();

    // add existing shares to QblFs list
    shares = this->getConfig()->getShares()->getList();
    for (shareIt = shares.begin(); shareIt != shares.end(); shareIt++) {
        QblFs *fs;

        fs = new QblFs(*shareIt);
        //fs->setRootPath((*shareIt)->getBasedir());
        this->fs.push_back(fs);
    }
    this->currentFs = this->fs.end();

    this->mac = new QblNetMac();

    // starting main thread
    mainThread = std::thread(&Qbl::runMainThread, this);

    return (retval);
}

void Qbl::newMessageReceived(QblMessage *message)
{
    std::list<IQbl *>::iterator iterator;

    for (iterator = listeners.begin(); iterator != listeners.end();
         iterator++) {
        (*iterator)->newMessageReceived(message);
    }
}

void Qbl::checkNextFs()
{
    std::unordered_set<std::string> state;
    std::unordered_set<std::string>::iterator iterator;

    if (this->fs.size() == 0) {
        return;
    }

    if (this->currentFs == this->fs.end()) {
        this->currentFs = this->fs.begin();
    } else {
        this->currentFs++;
        if (this->currentFs == this->fs.end()) {
            this->currentFs = this->fs.begin();
        }
    }

    state = (*this->currentFs)->compare();
    if (state.size() > 0) {
        QblBlockUpload *upload;
        // DELETE start
        int i = 0;

        for (iterator = state.begin(); iterator != state.end(); iterator++) {

        }
        // DELETE end

        upload = new QblBlockUpload((*this->currentFs)->getShare());
        std::string key = "asdfasdfasdfasdf";
        std::string url = "";
        upload->pack();
    }
    return;
}
