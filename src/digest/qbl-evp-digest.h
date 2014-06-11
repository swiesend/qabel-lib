/*
 * @file	 	qbl-sha256-digest.h
 * @brief		Main file to hash sha256 strings. (Header File)
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/evp.h>
#include <string>

#include "qbl-digest.h"

#ifndef __QBL_EVP_DIGEST_H__
#define __QBL_EVP_DIGEST_H__

class QblEvpDigest : public QblDigest {
public:
    /**
     * Constructor
     */
    QblEvpDigest();
    /**
     * Destructor
     */
    virtual ~QblEvpDigest();

    virtual void init();

    virtual void finish();

    virtual void onFinish();

    virtual void push(const std::vector<char> &data);

    virtual const EVP_MD *getAlgorithm() = 0;

    EVP_MD_CTX mdctx;
};

#endif
