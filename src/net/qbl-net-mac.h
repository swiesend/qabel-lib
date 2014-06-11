/**
 * @file		qbl-net-mac.h
 * @brief		Class for some network functions (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_NET_MAC_H__
#define __QBL_NET_MAC_H__

#include <stdint.h>
#include <stdlib.h>

#include <list>
using namespace std;

/**
 * Class QblNetMac: Class for some network functions
 */
class QblNetMac {
public:
    QblNetMac();
    virtual ~QblNetMac();

    const std::list<int64_t>& getMacAddresses() const;
    int64_t getFirstMacAddress();
    bool checkMacAddress(int64_t mac);

private:
    std::list<int64_t> macAddresses;

    void getMacAddresses();
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#elif __linux__
    int findMacAddress(const char *if_name);
#elif __MAC_10_6
#endif
};

#endif /* __QBL_NET_MAC_H__ */
