/*
 * @file    qbl-base64.cpp
 * @brief   Main file encode strings (base64) (header file)
 * @author  Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <string>
#include <string.h>
#include <vector>
#include <cstdio>
#include <netinet/in.h>
#include <cassert>
#include <stdexcept>
#include <resolv.h>

class QblBase64 {
    public:
        QblBase64();

        ~QblBase64();

        std::string FromBase64(std::vector<char>& binary);

        std::vector<char> ToBase64(const std::string& str);
};
