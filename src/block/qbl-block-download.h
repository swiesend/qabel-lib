/*
 * @file		qbl-block-download.h
 * @brief		Class for the download of files (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_BLOCK_DOWNLOAD_H__
#define __QBL_BLOCK_DOWNLOAD_H__

#include <sys/stat.h>

#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

#include "qbl-block.h"

/**
 * Class QblBlockDownload: Main class for the download of files
 */
class QblBlockDownload : public QblBlock {
public:

    /**
     * Constructor
     * TODO add authentification
     */
    QblBlockDownload();
    /**
     * Destructor
     */
    virtual ~QblBlockDownload();
    // TODO delete this, only for testing
    /**
     * Create a list of all entries
     */
    void list();
    /**
     * Create a list of all entries
     * @param data
     */
    void list(std::vector<char> data);
    // TODO delete this, only for testing
    void unpack();
    /**
     * Unpack data and read all information about the archive, do not save
     * data to disk
     * @param data data to unpack
     */
    void unpack(std::vector<char> data);

};

#endif /* __QBL_BLOCK_DOWNLOAD_H__ */
