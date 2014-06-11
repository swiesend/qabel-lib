/**
 * @file		qbl-socket.h
 * @brief		Class to open a socket connection (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_SOCKET_H__
#define __QBL_SOCKET_H__

#include <stdint.h>
#include <stdlib.h>

#include <string>
using namespace std;

class QblSocket {
public:
    QblSocket(std::string hostname, int port);
    virtual ~QblSocket();

    int connect();
    int close();
    virtual int sendMessage(uint8_t *message, size_t length) = 0;
    uint8_t *getResponse();
    std::string getErrorMessage();
    size_t getResponseSize() const;

protected:
    uint8_t *response;
    size_t responseSize;

    std::string getHostname();
    int getPort();
    int getFd();
    void createErrorMessage(std::string msg, int code = 0);

private:
    std::string hostname;
    int port;
    std::string errorMessage;
    int fd;
};

#endif /* __QBL_SOCKET_H__ */
