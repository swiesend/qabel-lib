/*
 * @file	 	qbl-sha256-digest.h
 * @brief		Main file to hash sha256 strings. (Header File)
 * @author      Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <openssl/evp.h>
#include <string>

#include "qbl-evp-digest.h"

#ifndef __QBL_SHA256_DIGEST_H__
#define __QBL_SHA256_DIGEST_H__

class QblSha256Digest : public QblEvpDigest {
public:
    /**
     * Constructor
     */
    QblSha256Digest();
    /**
     * Destructor
     */
    virtual ~QblSha256Digest();

    virtual const EVP_MD* getAlgorithm() {
        return EVP_sha256();
    }
};

#endif
