/**
 * @file		qbl-socket.cpp
 * @brief		Class to open a socket connection (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif

#include "qbl-socket.h"

QblSocket::QblSocket(std::string hostname, int port) :
        response(NULL), responseSize(0), hostname(hostname), port(port)
{

    return;
}

QblSocket::~QblSocket()
{
    if (this->response != NULL) {
        free(this->response);
    }

    return;
}

int QblSocket::connect()
{
    struct hostent *server;
    struct sockaddr_in addr;
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(1,1), &wsa_data);
#endif

    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd < 0) {
        this->createErrorMessage("Error opening socket", errno);
        return (-errno);
    }
    server = gethostbyname(this->hostname.data());
    if (server == NULL) {
        this->createErrorMessage("No host found");
        return (1);
    }
    memset((char *) &addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy((char *) &addr.sin_addr.s_addr, (char *) server->h_addr,
            server->h_length);
    addr.sin_port = htons(this->port);
    if (::connect(this->fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        this->createErrorMessage("Error connecting to socket", errno);
        return (-errno);
    }
    return 0;

}

int QblSocket::close()
{
    int retval;

    retval = ::close(this->fd);
    if (retval != 0) {
        this->createErrorMessage("Error closing socket", errno);
    }

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    WSACleanup();
#endif

    return (retval);
}

uint8_t *QblSocket::getResponse()
{
    return (this->response);
}

std::string QblSocket::getErrorMessage()
{
    return (this->errorMessage);
}

size_t QblSocket::getResponseSize() const
{
    return (this->responseSize);
}

std::string QblSocket::getHostname()
{
    return (this->hostname);
}

int QblSocket::getPort()
{
    return (this->port);
}

int QblSocket::getFd()
{
    return (this->fd);
}

void QblSocket::createErrorMessage(std::string msg, int code)
{
    this->errorMessage = msg;

    if (code != 0) {
        this->errorMessage.append(": ").append(strerror(errno)).append(" (")
                .append(std::to_string(code)).append(")");
    }

    return;
}
