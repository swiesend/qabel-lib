/*
 * @file    	qbl-aes-stream.cpp
 * @brief               Main file to de/encrypt a stream of data (Header File)
 * @author    	Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-aes-stream.h"

QblAesStream::QblAesStream()
{
    return;
}

QblAesStream::~QblAesStream()
{
    return;
}

const EVP_CIPHER *QblAesStream::getCipher() {
    return EVP_aes_256_cbc();
}
