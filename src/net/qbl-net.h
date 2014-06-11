/**
 * @file		qbl-net.h
 * @brief		Main class for net communication (Header file)
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

/**
 * Class QblNet: Main class for net communication
 */
class QblNet {
public:
    QblNet(std::string hostname, int port);
    virtual ~QblNet();

    uint8_t *getResponse();
    std::string getErrorMessage();
    size_t getResponseSize() const;

protected:
    uint8_t *response;
    size_t responseSize;

    std::string getHostname();
    int getPort();
    void createErrorMessage(std::string msg, int code = 0);

private:
    std::string hostname;
    int port;
    std::string errorMessage;
};

#endif /* __QBL_SOCKET_H__ */
