/*
 * @file	 	qbl-digest.h
 * @brief		Main file to hash strings. (Header File)
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */
 
#include "../qbl-pipe.h"
#include <openssl/evp.h>
#include <string>

#ifndef __QBL_DIGEST_H__
#define __QBL_DIGEST_H__

/**
 * Class QblDigest: Main file to digest a stream of data.
 */
class QblDigest : public QblPipe {
public:
	/**
	 * Constructor
	 */
	QblDigest();
	/**
	 * Destructor
	 */
	virtual ~QblDigest();

protected:
	virtual void init() = 0;

	EVP_MD_CTX mdctx;
};

#endif
