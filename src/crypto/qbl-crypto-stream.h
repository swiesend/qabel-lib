/*
 * @file		qbl-json-array.h
 * @brief		Main file to de/encrypt a stream of data (Header File)
 * @author              Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <string>
#include <list>
#include <exception>
#include <mutex>
#include <string>
#include "../qbl-pipe.h"

#ifndef __QBL_CRYPTO_STREAM_H__
#define __QBL_CRYPTO_STREAM_H__

#define BUFFER_LENGTH 1024

enum QBL_CRYPTO_STREAM_MODE {
    QBL_CRYPTO_STREAM_ENCRYPT,
    QBL_CRYPTO_STREAM_DECRYPT
};
/**
 * Class QblCryptoStream: Main file to de/encrypt a stream of data (Header File)
 * @todo make decrypt/encrypt/init/finish abstract to support multiple ciphers
 */
class QblCryptoStream : public QblPipe {
public:
    /**
     * Constructor
     */
    QblCryptoStream();
    /**
     * Destructor
     */
    virtual ~QblCryptoStream();

    virtual void init(const std::vector<char> /*key*/, const std::vector<char> /*iv*/,
            QBL_CRYPTO_STREAM_MODE mode)
    {
        this->mode = mode;
    };

    QBL_CRYPTO_STREAM_MODE getMode() {
        return mode;
    }

    virtual void push(const std::vector<char> &data) {
        char arr[data.size()];
        std::copy(data.begin(), data.end(), arr);
        if(this->mode == QBL_CRYPTO_STREAM_DECRYPT) {
            this->decrypt(arr, data.size());
        } else {
            this->encrypt(arr, data.size());
        }
    }

protected:

    virtual void finish() = 0;

    virtual void decrypt(const char *plain, const int length) = 0;

    virtual void encrypt(const char *encrypted, const int length) = 0;

private:
    QBL_CRYPTO_STREAM_MODE mode;
};

#endif                          /* __QBL_JSON_ARRAY_H__ */
