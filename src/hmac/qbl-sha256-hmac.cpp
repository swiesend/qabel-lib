/*
 * @file	 	qbl-digest.cpp
 * @brief		Main file to hash strings.
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-sha256-hmac.h"

QblSha256Hmac::QblSha256Hmac() {

}

QblSha256Hmac::~QblSha256Hmac(){

}

void QblSha256Hmac::init(const std::vector<char> &key) {
	HMAC_CTX_init(&this->hmacCtx);
	HMAC_Init_ex(&this->hmacCtx, &key[0], key.size(), EVP_sha256(), NULL);
}

void QblSha256Hmac::push(const std::vector<char> &data) {
	HMAC_Update(&this->hmacCtx, (unsigned char*)&data[0], data.size());
}

void QblSha256Hmac::finish() {
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int length;
	HMAC_Final(&this->hmacCtx, hash, &length);
	HMAC_CTX_cleanup(&this->hmacCtx);

	getListener()->onData(std::vector<char>(hash, hash + length));
	getListener()->onFinish();
}
