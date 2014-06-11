/**
 * @file		qbl-web.cpp
 * @brief		Class to send and receive web message (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>


#include "qbl-web.h"

QblWeb::QblWeb(std::string hostname, int port) :
    QblNet(hostname, port)
{

    return;
}

QblWeb::~QblWeb()
{

    return;
}

int QblWeb::getErrorCode()
{
    return (this->errorCode);
}

const std::string& QblWeb::getDate() const
{
	return (this->date);
}

void QblWeb::checkResponse()
{
    char *buffer;
    long val;
    if (this->response == NULL) {
        this->errorCode = -1;
        return;
    }
    buffer = strchr((char *)this->response, ' ');
    if (buffer == NULL) {
        this->errorCode = -1;
        return;
    }
    buffer++;
    
    errno = 0;
    val = strtol(buffer, NULL, 10);
    
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        return;
    } else {
        this->errorCode = (int)val;
    }

    
    buffer = (char *)this->response;
    while (true) {
        buffer = strchr(buffer, '\n');
        buffer++;
        if (! strncmp(buffer, "Date:", 5)) {
            buffer = strchr(buffer, ' ');
            buffer++;

            this->date = buffer;
            this->date = this->date.substr(0, this->date.find("\n"));
            auto f = this->date.find("\r");
            if (f != std::string::npos) {
                this->date = this->date.substr(0, f);
            }

        }

        if (buffer[1] == '\n') {
            break;
        }
    }

    return;
}
