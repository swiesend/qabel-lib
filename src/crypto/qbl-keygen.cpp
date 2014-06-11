/*
 * @file    	qbl-keygen.cpp
 * @brief       Main file to generate keys
 * @author    	Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-keygen.h"
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>

static std::vector<char> randomBytes(unsigned int size) {
	char bytes[size];
	RAND_bytes((unsigned char*)bytes, size);
	return std::vector<char>(bytes, bytes+size);
}

std::vector<char> qblKeyGenAes256() {
	return randomBytes(32);
}

std::vector<char> qblKeyGenAes256IV() {
	return randomBytes(AES_BLOCK_SIZE);
}

EVP_PKEY *qblKeyGenRsa(int keysize) {
	EVP_PKEY_CTX *ctx;
	EVP_PKEY *pkey = NULL;
	ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	if (!ctx)
		return NULL;
	if (EVP_PKEY_keygen_init(ctx) <= 0)
		return NULL;
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, keysize) <= 0)
		return NULL;

	if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
		return NULL;
	return pkey;
}
