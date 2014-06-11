/*
 * @file		qbl-zlib.h
 * @brief		Main class for compress and decompress buffer (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_ZLIB_H__
#define __QBL_ZLIB_H__

#include <zlib.h>

#include <vector>
using namespace std;

/**
 * Class QblZlib: Main class for compress and decompress buffer
 */
class QblZlib {

public:
    /**
     * Constructor
     */
    QblZlib();

    /**
     * Destructor
     */
    virtual ~QblZlib();

    /**
     * Compress data
     * @param data Data to compress
     * @return Compressed data
     */
    std::vector<char> compress(std::vector<char> data);
    /**
     * Decompress data
     * @param data Data to decompress
     * @return Decompress data
     */
    std::vector<char> decompress(std::vector<char> data);

private:
    z_stream stream;

    void errorMessage(int id);
};

#endif                              // __QBL_ZLIB_H__
