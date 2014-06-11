/*
 * @file    	qbl-evp-stream.cpp
 * @brief               Main file to de/encrypt a stream of data (Header File)
 * @author    	Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-evp-stream.h"

QblEvpStream::QblEvpStream()
{
    return;
}

QblEvpStream::~QblEvpStream()
{
    return;
}

void QblEvpStream::decrypt(const char *encrypted, const int length)
{
    int outlength;
    unsigned char buffer[length + EVP_MAX_BLOCK_LENGTH];
    EVP_DecryptUpdate(&this->decryptContext, buffer, &outlength, (unsigned char *)encrypted, length);

    if(outlength != 0) {
        std::vector<char> vect(buffer, buffer + length);
        getListener()->onData(vect);
    }
}

void QblEvpStream::encrypt(const char *plain, const int length)
{
    int outlength;
    unsigned char buffer[length + EVP_MAX_BLOCK_LENGTH];
    EVP_EncryptUpdate(&this->encryptContext, buffer, &outlength, (unsigned char *)plain, length);

    if(outlength != 0) {
        std::vector<char> vect(buffer, buffer + length);
        getListener()->onData(vect);
    }
}

void QblEvpStream::init(const std::vector<char> key, const std::vector<char> iv, QBL_CRYPTO_STREAM_MODE mode)
{
    QblCryptoStream::init(key, iv, mode);
    EVP_CIPHER_CTX_init(&this->encryptContext);
    const EVP_CIPHER *cipher = this->getCipher();
    EVP_EncryptInit_ex(&this->encryptContext, cipher, NULL, (unsigned char *)key.data(), (unsigned char *)iv.data());

    EVP_CIPHER_CTX_init(&this->decryptContext);
    EVP_DecryptInit_ex(&this->decryptContext, cipher, NULL, (unsigned char *)key.data(), (unsigned char *)iv.data());
}

void QblEvpStream::finish()
{
    int length;
    unsigned char buffer[EVP_MAX_BLOCK_LENGTH];
	if(this->getMode() == QBL_CRYPTO_STREAM_ENCRYPT) {
		EVP_EncryptFinal_ex(&this->encryptContext, buffer, &length);
		if(length != 0) {
			std::vector<char> vect(buffer, buffer + length);
			getListener()->onData(vect);
		}
	}
	else {
		EVP_DecryptFinal_ex(&this->decryptContext, buffer, &length);
		if(length != 0) {
			std::vector<char> vect(buffer, buffer + length);
			getListener()->onData(vect);
		}
	}
    getListener()->onFinish();
}
