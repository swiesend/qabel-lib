/**
 * @file		qbl-net-mac.cpp
 * @brief		Class for some network functions (Implementation)
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
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <stdio.h>
#endif

#include "qbl-net-mac.h"

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#elif __linux__
#define BUFFER_LEN 1024
#define SEARCH_LEN 10
#endif

QblNetMac::QblNetMac()
{
    this->getMacAddresses();

    return;
}

QblNetMac::~QblNetMac()
{
    return;
}

const std::list<int64_t>& QblNetMac::getMacAddresses() const
{
    return (this->macAddresses);
}

int64_t QblNetMac::getFirstMacAddress()
{
    return (*this->macAddresses.begin());
}

bool QblNetMac::checkMacAddress(int64_t mac)
{
    std::list<int64_t>::iterator iterator;

    for (iterator = this->macAddresses.begin();
            iterator != this->macAddresses.end(); iterator++) {
        if (*iterator == mac) {
            return (true);
        }
    }

    return (false);
}

void QblNetMac::getMacAddresses()
{
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#elif __linux__
	int line_len, buffer_len;
    FILE *file;
    char line[BUFFER_LEN], *buffer, search[SEARCH_LEN];

    file = fopen("/proc/net/dev", "r");
    if(errno) {
        // TODO testing on different Linux distribution
        // and delete next lines
        this->macAddresses.push_back(0);

        return;
    }

    while(fgets(line, BUFFER_LEN, file)) {
        buffer = strchr(line, ':');
        if(buffer == NULL) {
            continue;
        }
        line_len = strlen(line);
        buffer_len = strlen(buffer);
        line[line_len - buffer_len] = '\0';
        buffer = strrchr(line, ' ');
        if(buffer == NULL) {
            continue;
        }
        buffer++;

        this->findMacAddress(buffer);
    }
    pclose(file);

#endif

    if (this->macAddresses.size() == 0) {
        this->macAddresses.push_back(0);
    }

    return;
}

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#elif __linux__
int QblNetMac::findMacAddress(const char* if_name)
{
	int fd;
	struct ifreq ifr;
    int64_t mac;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	close(fd);

    mac = 0;
    memcpy(&mac, &ifr.ifr_hwaddr.sa_data, 6);
    if (mac == 0) {
        return (0);
    }

    this->macAddresses.push_back(mac);

    return (0);
}
#elif __MAC_10_6
#endif
