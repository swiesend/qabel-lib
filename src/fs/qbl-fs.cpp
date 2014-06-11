/*
 * @file        qbl-digest.h
 * @brief       Main file for filesystem operations.
 * @author      Jan Schreiber <schreiber@praemandatum.de>
 *              Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

/*
 * @TODO: The comperator is only allowed to run when there is *no* sync running.
 */

#include "qbl-fs.h"

#define PATH_SEPERATOR '/'

QblFs::QblFs(QblJsonMainConfigShare *share) :
    share(share)
{
    this->rootPath = this->share->getBasedir();

    return;
}

QblFs::~QblFs()
{

    return;
}

void QblFs::index(const std::string &path, QblFsState &list)
{
    DIR *dir;
    struct dirent *dirEnt;
    struct stat finfo;

    stat(path.c_str(), &finfo);

    if (S_ISREG(finfo.st_mode) || S_ISDIR(finfo.st_mode)) {
        list.insert(std::make_pair(path, finfo.st_mtime));
    }
    if (S_ISDIR(finfo.st_mode)) {
        dir = opendir(path.c_str());
        if (dir == NULL) {
            throw QblException { "No file or directory was applied" };
        }
        while ((dirEnt = readdir(dir)) != NULL) {
            if (std::strcmp(".", dirEnt->d_name) == 0
                    || std::strcmp("..", dirEnt->d_name) == 0) {
                continue;
            }
            std::string childPath = path + PATH_SEPERATOR + dirEnt->d_name;
            index(childPath, list);
        }
        closedir(dir);
    }
    //@TODO print warning if no directory is supplied.
}

std::unordered_set<std::string> QblFs::compare()
{
    std::unordered_set<std::string> result;
    QblFsState newState;
    index(getRootPath(), newState);

    QblFsState::const_iterator it;

    for (it = newState.begin(); it != newState.end(); it++) {
        QblFsState::iterator oldEntry = this->state.find(it->first);

        if (oldEntry == this->state.end() || it->second != oldEntry->second) {
            result.insert(it->first);
        }
        if (oldEntry != this->state.end())
            state.erase(oldEntry);
    }

    for (it = this->state.begin(); it != this->state.end(); it++) {
        result.insert(it->first);
        state.erase(it);
    }

    this->state = newState;

    return (result);
}

QblJsonMainConfigShare*& QblFs::getShare()
{
    return (this->share);
}
