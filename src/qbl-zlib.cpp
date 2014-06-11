/*
 * @file		qbl-zlib.cpp
 * @brief		Main class for compress and decompress buffer (Implementation)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <errno.h>

#include "qbl.h"
#include "qbl-zlib.h"

/* CHUNK is the size of the memory chunk used by the zlib routines. */
#define CHUNK 0x4000

/* These are parameters to deflateInit2. */
#define windowBits 15
#define GZIP_ENCODING 16
#define ENABLE_ZLIB_GZIP 32

QblZlib::QblZlib()
{
    this->stream.zalloc = Z_NULL;
    this->stream.zfree = Z_NULL;
    this->stream.opaque = Z_NULL;

    return;
}

QblZlib::~QblZlib()
{
    return;
}

std::vector<char> QblZlib::compress(std::vector<char> data)
{
    std::vector<char> result;
    int retval;
    this->stream.next_in = Z_NULL;
    this->stream.avail_in = 0;

    retval = deflateInit2(&this->stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
            windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY);
    if (retval < 0) {
        this->errorMessage(retval);
    }

    this->stream.next_in = (unsigned char *)data.data();
    this->stream.avail_in = data.size();

    do {
        int n, retval;
        unsigned char buffer[CHUNK];
        std::vector<char> _buffer;

        this->stream.avail_out = CHUNK;
        this->stream.next_out = buffer;
        retval = deflate(&this->stream, Z_FINISH);
        if (retval < 0) {
            (void)deflateEnd(&this->stream);
            this->errorMessage(retval);
        }
        n = CHUNK - this->stream.avail_out;
        _buffer.insert(_buffer.begin(), buffer, buffer + n);
        result.insert(result.end(), _buffer.begin(), _buffer.end());

    } while (this->stream.avail_out == 0);

    (void)deflateEnd(&this->stream);
    return (result);
}

std::vector<char> QblZlib::decompress(std::vector<char> data)
{
    int retval;
    std::vector<char> result;
    std::vector<char>::iterator begin, end;
    unsigned char in[CHUNK];
    size_t current = 0;

    this->stream.next_in = Z_NULL;
    this->stream.avail_in = 0;

    retval = inflateInit2(&this->stream, windowBits | ENABLE_ZLIB_GZIP);
    if (retval < 0) {
        this->errorMessage(retval);
    }

    do {
        std::vector<char> in;
        size_t length;

        begin = data.begin();
        begin += current;
        end = begin;
        if (data.size() - current > CHUNK) {
            length = CHUNK;
        } else {
            length = data.size() - current;
        }
        end += length;
        in.resize(length);
        in.insert(in.begin(), begin, end);
        this->stream.next_in = (unsigned char *)in.data();
        this->stream.avail_in = length;

        do {
            int n, retval;
            unsigned char buffer[CHUNK];

            this->stream.avail_out = CHUNK;
            this->stream.next_out = buffer;
            retval = inflate(&this->stream, Z_NO_FLUSH);
            if (retval != Z_STREAM_ERROR) {
                switch (retval) {
                case Z_NEED_DICT:
                    retval = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&this->stream);
                    this->errorMessage(retval);
                }
            }
            n = CHUNK - this->stream.avail_out;
            std::vector<char> _buffer(buffer, buffer + n);
            result.insert(result.end(), _buffer.begin(), _buffer.end());

        } while (this->stream.avail_out == 0);

        if (length < CHUNK) {
            break;
        }
        current += length;

    } while (retval != Z_STREAM_END);

    (void)inflateEnd(&this->stream);
    return (result);
}

void QblZlib::errorMessage(int id)
{
    std::string errmsg;

    errmsg = "Error compress data";
    std::string errorNumber = std::to_string(id);
    std::string errorDesc(zError(id));
    throw QblException { errmsg, errorNumber, errorDesc };

    return;
}

