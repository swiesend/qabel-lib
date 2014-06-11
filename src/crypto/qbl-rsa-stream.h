/*
 * @file		qbl-evp-stream.h
 * @brief		Main file to de/encrypt a stream of data (Header File)
 * @author              Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <vector>
#include "qbl-crypto-stream.h"

#ifndef __QBL_RSA_STREAM_H__
#define __QBL_RSA_STREAM_H__

#define BUFFER_LENGTH 1024

/**
 * Class QblRsaStream: Main file to de/encrypt a stream of data (Header File)
 * @todo make decrypt/encrypt/init/deinit abstract to support multiple ciphers
 */
class QblRsaStream : public QblPipe {
public:
    /**
     * Constructor
     */
    QblRsaStream();
    /**
     * Destructor
     */
    virtual ~QblRsaStream();

    void init(RSA *key, QBL_CRYPTO_STREAM_MODE mode);

    virtual void push(const std::vector<char> &data);

    virtual void finish();

private:
    std::vector<char> buffer;
    RSA* key;
    QBL_CRYPTO_STREAM_MODE mode;
};

#endif
