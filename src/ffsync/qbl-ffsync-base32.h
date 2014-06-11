/*
 * @file		qbl-json-main-config-ffsync-user.h
 * @brief		Class to encode a string to Base32 (Header File)
 * @author		Andre Fricke <afr@michael-wessel.de>
 * @author		Marcus Amler <ma@michael-wessel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_FFSYNC_BASE32_H__
#define __QBL_FFSYNC_BASE32_H__

#include <string>
#include <vector>

class QblFFSyncBase32 {
public:

    /**
     * Constructor
     */
    QblFFSyncBase32();

    /**
     * Destructor
     */
    ~QblFFSyncBase32();

//    static std::string encode_Base32(std::string data);
std::string encode_Base32(std::vector<char> data);
//    std::string decode_Base32(std::string data);
	std::vector<char> decode_Base32(std::string data);
    int IndexOf(std::string &text, char &pattern);

private:

};

#endif 
