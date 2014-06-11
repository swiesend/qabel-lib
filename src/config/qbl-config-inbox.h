/*
 * @file		qbl-config-inbox.h
 * @brief		Get data from inbox (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CONFIG_INBOX_H__
#define __QBL_CONFIG_INBOX_H__

#include <string>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;

class QblConfigInbox {
public:
    QblConfigInbox(std::string inbox);
    QblConfigInbox(std::string server, std::string uri, std::string protocol,
            int port = 443);
    virtual ~QblConfigInbox();
    const std::string getInbox() const;
    int getPort() const;
    const std::string& getServer() const;
    const std::string& getUri() const;

private:
    std::string protocol;
    std::string server;
    int port;
    std::string uri;

    void splitInbox(std::string inbox);
};

#endif /* __QBL_CONFIG_INBOX_H__ */
