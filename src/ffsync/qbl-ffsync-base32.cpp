/*
 * @file		qbl-json-main-config-ffsync-user.cpp
 * @brief		Class to encode a string to Base32 (Implementation)
 * @author		Andre Fricke <afr@michael-wessel.de>
 * @author		Marcus Amler <ma@michael-wessel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */
 
#include "qbl-ffsync-base32.h"
#include <vector>
#include "utf8.h"
#include <sstream>
#include <iostream>
#include <ctime>

QblFFSyncBase32::QblFFSyncBase32()
{
    return;
}

QblFFSyncBase32::~QblFFSyncBase32()
{
    return;
}

std::string QblFFSyncBase32::encode_Base32(std::vector<char> data)
{
    std::string b32_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    std::string returnv;

    //Save original length of inp ut data
    int dataLength = data.size();

    for(int i = 0; i < dataLength; i += 5)
    {
        returnv += b32_chars.at((unsigned char)data[i] >> 3);
        if(i == dataLength) //Should never happen
        {
            returnv += "=======";
            return returnv;
        }
        returnv += b32_chars.at( ((((unsigned char)data[i]) & 0x07) << 2) | (((unsigned char)data[i+1] & 0xc0) >> 6));
        if(i == dataLength - 1)
        {
            returnv += "======";
            return returnv;
        }
        returnv += b32_chars.at(((unsigned char)data[i+1] & 0x3e) >> 1);
        returnv += b32_chars.at((((unsigned char)data[i+1] & 0x01) << 4) | (((unsigned char)data[i+2] & 0xf0) >> 4));
        if(i == dataLength - 2)
        {
            returnv += "====";
            return returnv;
        }
        returnv += b32_chars.at((((unsigned char)data[i+2] & 0x0f) << 1) | (((unsigned char)data[i+3] & 0x80) >> 7));
        if(i == dataLength - 3)
        {
            returnv += "===";
            return returnv;
        }
        returnv += b32_chars.at(((unsigned char)data[i+3] & 0x7c) >> 2);
        returnv += b32_chars.at((((unsigned char)data[i+3] & 0x03) << 3) | (((unsigned char)data[i+4] & 0xe0) >> 5));
        if(i == dataLength - 4)
        {
            returnv += "=";
            return returnv;
        }
        data.push_back('\0');
        returnv += b32_chars.at(((unsigned char)data[i+4] & 0x1f));
    }
    return returnv;
}

std::vector<char> QblFFSyncBase32::decode_Base32(std::string data)
{
    char p = '=';
    std::vector<char> returnv;
    std::string b32_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    int len = IndexOf(data, p);
    if(len < 0)
    {
        len = data.length();
    }

    returnv.reserve(len*5/8);

    int buffer = 0;
    int bufferedBits = 0;
    int charValue = 0;

    for(int i = 0; i < len; i++)
    {
        charValue = IndexOf(b32_chars,data.at(i));

        if(charValue >= 0)
        {
            buffer = buffer << 5;
            buffer = buffer | charValue;
            bufferedBits = bufferedBits + 5;
            if(bufferedBits > 7)
            {
                returnv.push_back((char)((buffer >> (bufferedBits - 8)) & 0xFF));
                bufferedBits = bufferedBits - 8;
            }
        }
    }

    return returnv;
}

int QblFFSyncBase32::IndexOf(std::string &text, char &pattern)
{
    // where appears the pattern in the text?
    std::string::size_type loc = text.find(pattern, 0);
    if(loc != std::string::npos)
    {
        return loc;
    }
    else
    {
        return -1;
    }
}
