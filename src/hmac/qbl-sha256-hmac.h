/*
 * @file	 	qbl-digest.h
 * @brief		Main file to hash strings. (Header File)
 * @author              Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */
 
#include "../qbl-pipe.h"
#include <openssl/hmac.h>
#include <string>

#ifndef __QBL_HMAC_H__
#define __QBL_HMAC_H__

/**
 * Class QblHmac: Main file to digest a stream of data.
 */
class QblSha256Hmac : public QblPipe {
public:
	/**
	 * Constructor
	 */
	QblSha256Hmac();
	/**
	 * Destructor
	 */
	virtual ~QblSha256Hmac();
	
	virtual void init(const std::vector<char> &key);

protected:

	virtual void push(const std::vector<char> &data);

	virtual void finish();

private:
	HMAC_CTX hmacCtx;
};

#endif
