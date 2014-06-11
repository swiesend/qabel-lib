/*
 * @file        qbl-fs.h
 * @brief       Main file for filesystem operations. (Header File)
 * @author      Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_FS_H__
#define __QBL_FS_H__


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <cstring>
#include <exception>

#include "qbl.h"
#include "qbl-json-main-config-share.h"

typedef std::unordered_map<std::string, time_t> QblFsState;

class QblFs {
public:
    QblFs(QblJsonMainConfigShare *share);

    virtual ~QblFs();

    /** TODO: only for testing -> Delete later */
    inline void setRootPath(const std::string &rootPath) {
        this->rootPath = rootPath;
    }

    inline const std::string getRootPath() {
        return this->rootPath;
    }
    QblJsonMainConfigShare*& getShare();

    std::unordered_set<std::string> compare();

private:
    QblJsonMainConfigShare *share;
    QblFsState state;
    std::string rootPath;

    void index(const std::string &path, QblFsState &list);
};

#endif
