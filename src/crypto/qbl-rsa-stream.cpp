/*
 * @file    	qbl-evp-stream.cpp
 * @brief       Main file to de/encrypt a stream of data (Header File)
 * @author    	Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-rsa-stream.h"
#include <openssl/pem.h>

#define RSA_PADDING RSA_PKCS1_PADDING

QblRsaStream::QblRsaStream()
{
    return;
}

QblRsaStream::~QblRsaStream()
{
    return;
}

void QblRsaStream::init(RSA *key, QBL_CRYPTO_STREAM_MODE mode)
{
	this->mode = mode;
    this->key = key;

    return;
}

void QblRsaStream::push(const std::vector<char> &data) {
	buffer.insert(buffer.end(), data.begin(), data.end());
}

void QblRsaStream::finish()
{
    unsigned char *result;
    int length;

    result = new unsigned char[RSA_size(key)];
    if(mode == QBL_CRYPTO_STREAM_ENCRYPT) { 
        length = RSA_public_encrypt(buffer.size(), (unsigned char *)&buffer[0],
                result, key, RSA_PKCS1_OAEP_PADDING);
    }
    else {
        length = RSA_private_decrypt(buffer.size(), (unsigned char *)&buffer[0],
                result, key, RSA_PKCS1_OAEP_PADDING);
    }
    std::vector<char> vect(result, result + length);
    getListener()->onData(vect);
    getListener()->onFinish();

    return;
}
