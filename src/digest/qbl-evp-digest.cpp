/*
 * @file	 	qbl-sha256-digest.cpp
 * @brief		Main file to hash sha256 strings.
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */
 
#include "qbl-evp-digest.h"

QblEvpDigest::QblEvpDigest() {

}

QblEvpDigest::~QblEvpDigest(){

}

void QblEvpDigest::init() {
    EVP_MD_CTX_init(&mdctx);
    EVP_DigestInit_ex(&mdctx, getAlgorithm(), NULL);
}

void QblEvpDigest::push(const std::vector<char> &data){
    char arr[data.size()];
    std::copy(data.begin(), data.end(), arr);
    EVP_DigestUpdate(&mdctx, (const unsigned char *)arr, (const unsigned int)data.size());
}

void QblEvpDigest::finish(){
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length;
    EVP_DigestFinal_ex(&mdctx, hash, &length);
    EVP_MD_CTX_cleanup(&mdctx);

    std::vector<char> vect(hash, hash + length);
    getListener()->onData(vect);
    getListener()->onFinish();
}

void QblEvpDigest::onFinish(){}
