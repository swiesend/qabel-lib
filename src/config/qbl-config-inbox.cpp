/*
 * @file		qbl-config-inbox.cpp
 * @brief		Get data from inbox (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "qbl-config-inbox.h"

QblConfigInbox::QblConfigInbox(std::string inbox)
{
    this->splitInbox(inbox);

    return;
}

QblConfigInbox::QblConfigInbox(std::string server, std::string uri,
        std::string protocol, int port) :
        protocol(protocol), server(server), port(port), uri(uri)
{
    return;
}

QblConfigInbox::~QblConfigInbox()
{
    return;
}

const std::string& QblConfigInbox::getServer() const
{
    return (this->server);
}

int QblConfigInbox::getPort() const
{
    return (this->port);
}

const std::string& QblConfigInbox::getUri() const
{
    return (this->uri);
}

const std::string QblConfigInbox::getInbox() const
{
    std::string result;

    if (this->protocol.length() > 0) {
        result.append(this->protocol).append("://");
    }

    result.append(this->server).append(":").append(std::to_string(this->port))
            .append(this->uri);

    return (result);
}

void QblConfigInbox::splitInbox(std::string inbox)
{
    std::string buffer;
    size_t found;
    int countServer = 0;
    int countPort = 0;
    bool foundOne = false;
    errno = 0;
    buffer = inbox;
    /**
     * Search for slashes
     * */
    while (1) {
        found = buffer.find("/");
        if (found != std::string::npos) {
            countServer += found + 1;
            buffer = inbox.substr(countServer);
            if (buffer.at(1) == '/') {
                continue;
            }
        } else {
            break;
        }
    }

    this->uri = buffer;

    /**
     * Search for :
     * */
    countPort = 0;
    buffer = inbox;
    while (1) {
        found = buffer.find(":");
        if (found != std::string::npos) {
            countPort += found + 1;
            buffer = inbox.substr(countPort);
            if (buffer.at(1) == '/') {
                continue;
            }
            foundOne = true;
            break;
        } else {
            break;
        }
    }

    if (foundOne == false) {
        this->server = inbox.substr(0, countServer - 1);
        if (this->server.find("https") != std::string::npos) {
            this->port = 443;
        }
    } else {
        this->server = inbox.substr(0, countPort - 1);
        long port = strtol(inbox.substr(countPort, countServer).c_str(), NULL, 10);

        if((errno == ERANGE && (port == LONG_MAX || port == LONG_MIN))
                || (errno != 0 && port == 0)) {
            return;
        }
        else {
            this->port = (int)port;
        }
    }


    /**
     * Search for protocol
     * */
    foundOne = false;
    buffer = this->server;
    found = buffer.find(":");
    if (found != std::string::npos) {
        this->protocol = this->server.substr(0, found);
        this->server = this->server.substr(found + 3, this->server.length());
    } else {
        this->protocol = "";
    }

    return;
}
