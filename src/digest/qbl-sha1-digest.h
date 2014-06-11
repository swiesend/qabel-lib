/*
 * @file	 	qbl-sha1-digest.h
 * @brief		Main file to hash sha1 strings. (Header File)
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/evp.h>
#include <string>

#include "qbl-evp-digest.h"

#ifndef __QBL_SHA1_DIGEST_H__
#define __QBL_SHA1_DIGEST_H__

class QblSha1Digest : public QblEvpDigest {
public:
    /**
     * Constructor
     */
    QblSha1Digest();
    /**
     * Destructor
     */
    virtual ~QblSha1Digest();

    virtual const EVP_MD* getAlgorithm() {
        return EVP_sha1();
    }
};

#endif
