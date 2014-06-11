/*
 * @file		qbl-aes-stream.h
 * @brief		Main file to de/encrypt a stream of data (Header File)
 * @author              Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/evp.h>
#include <string>
#include "qbl-evp-stream.h"

#ifndef __QBL_AES_STREAM_H__
#define __QBL_AES_STREAM_H__

#define BUFFER_LENGTH 1024

/**
 * Class QblAesStream: Main file to de/encrypt a stream of data (Header File)
 * @todo make decrypt/encrypt/init/deinit abstract to support multiple ciphers
 */
class QblAesStream : public QblEvpStream {
public:
    /**
     * Constructor
     */
    QblAesStream();
    /**
     * Destructor
     */
    virtual ~QblAesStream();

protected:
    virtual const EVP_CIPHER *getCipher();

private:
    EVP_CIPHER_CTX encryptContext;
    EVP_CIPHER_CTX decryptContext;
};

#endif
