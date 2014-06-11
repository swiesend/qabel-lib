/**
 * @file		qbl-net.cpp
 * @brief		Class to open a socket connection (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#if 0
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif
#endif

#include <errno.h>
#include <string.h>

#include "qbl-net.h"

QblNet::QblNet(std::string hostname, int port) :
    response(NULL), responseSize(0), hostname(hostname), port(port)
{

    return;
}

QblNet::~QblNet()
{
    if (this->response != NULL) {
        free(this->response);
    }

    return;
}

uint8_t *QblNet::getResponse()
{
    return (this->response);
}

std::string QblNet::getErrorMessage()
{
    return (this->errorMessage);
}

size_t QblNet::getResponseSize() const
{
    return (this->responseSize);
}

std::string QblNet::getHostname()
{
    return (this->hostname);
}

int QblNet::getPort()
{
    return (this->port);
}

void QblNet::createErrorMessage(std::string msg, int code)
{
    this->errorMessage = msg;

    if (code != 0) {
        this->errorMessage.append(": ").append(strerror(errno)).append(" (")
                .append(std::to_string(code)).append(")");
    }

    return;
}
