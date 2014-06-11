/*
 * @file		qbl-evp-stream.h
 * @brief		Main file to de/encrypt a stream of data (Header File)
 * @author              Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/evp.h>
#include <string>
#include "qbl-crypto-stream.h"

#ifndef __QBL_EVP_STREAM_H__
#define __QBL_EVP_STREAM_H__

#define BUFFER_LENGTH 1024

/**
 * Class QblEcpStream: Main file to de/encrypt a stream of data (Header File)
 * @todo make decrypt/encrypt/init/deinit abstract to support multiple ciphers
 */
class QblEvpStream : public QblCryptoStream {
public:
    /**
     * Constructor
     */
    QblEvpStream();
    /**
     * Destructor
     */
    virtual ~QblEvpStream();

    virtual void init(const std::vector<char> key, const std::vector<char> iv, QBL_CRYPTO_STREAM_MODE mode);

    virtual void decrypt(const char *plain, const int length);

    virtual void encrypt(const char *encrypted, const int length);

    virtual void finish();

protected:

    virtual const EVP_CIPHER *getCipher() = 0;

private:
    EVP_CIPHER_CTX encryptContext;
    EVP_CIPHER_CTX decryptContext;
};

#endif
