/*
 * @file		qbl-block-download.cpp
 * @brief		Main class for the and download of files (Implementation)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence 
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <dirent.h>
#include <sys/types.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "qbl.h"
#include "qbl-block-download.h"
#include "qbl-sha256-digest.h"
#include "qbl-block-result-listener.h"
#include "qbl-zlib.h"

QblBlockDownload::QblBlockDownload()
{

    return;
}

QblBlockDownload::~QblBlockDownload()
{

    return;
}

void QblBlockDownload::list()
{
    std::vector<char> buffer;
    std::ifstream file;

    file.open("test.gz", std::ios_base::binary);
    if (file) {
        std::streampos length;
#if 0
        QblBlockResultListener *listener;
        QblSha256Digest digest;
        QblBlockBlob blob;
#endif

        file.seekg(0, std::ios::end);
        length = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(length);
        file.read(&buffer[0], length);
        file.close();

        this->list(buffer);
    }

    return;
}

void QblBlockDownload::list(std::vector<char> data)
{
    std::vector<char> buffer;

    // TODO decrypt file

    // zlib
    QblZlib *zlib;
    zlib = new QblZlib();
    buffer = zlib->decompress(data);

    if (this->parseHeader(buffer.begin()) != 0) {
        std::string errmsg;
        errmsg = "Error parse header from received data";
        throw QblException { errmsg };
    }
    // TODO delete only for testing
    std::ofstream out;
    out.open("test.log", std::ios_base::binary);
    if (out) {
        out.write(&buffer[0], buffer.size());
        out.close();
    }

    return;
}

void QblBlockDownload::unpack()
{
    std::vector<char> buffer;
    std::ifstream file;

    file.open("test.gz", std::ios_base::binary);
    if (file) {
        std::streampos length;

        file.seekg(0, std::ios::end);
        length = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(length);
        file.read(&buffer[0], length);
        file.close();

        this->unpack(buffer);
    }

    return;
}

void QblBlockDownload::unpack(std::vector<char> data)
{
    // TODO decrypt file

    // zlib
    QblZlib *zlib;
    zlib = new QblZlib();
    this->data = zlib->decompress(data);

    if (this->parseHeader(this->data.begin()) != 0) {
        std::string errmsg;
        errmsg = "Error parse header from received data";
        throw QblException { errmsg };
    }
    if (this->parseData(this->startData) != 0) {
        std::string errmsg;
        errmsg = "Error parse data from received data";
        throw QblException { errmsg };
    }
    // TODO delete only for testing
    std::ofstream out;
    out.open("test.log", std::ios_base::binary);
    if (out) {
        out.write(&this->data[0], this->data.size());
        out.close();
    }

    return;
}
