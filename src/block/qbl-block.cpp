/*
 * @file		qbl-block.cpp
 * @brief		Main class for the up- and download of files (Implementation)
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
#include "qbl-block.h"
#include "qbl-sha256-digest.h"
#include "qbl-block-result-listener.h"
#include "qbl-zlib.h"

#define STR_TREE "tree "
#define STR_TREE_TREE "TREE"
#define STR_BLOB "blob "
#define STR_TREE_FILE "FILE"
#define HASH_LENGTH 0x40
#define INT_S_ISUID 4000
#define INT_S_ISGID 2000
#define INT_S_ISVTX 1000
#define INT_S_IRUSR  400
#define INT_S_IWUSR  200
#define INT_S_IXUSR  100
#define INT_S_IRGRP   40
#define INT_S_IWGRP   20
#define INT_S_IXGRP   10
#define INT_S_IROTH    4
#define INT_S_IWOTH    2
#define INT_S_IXOTH    1

QblBlock::QblBlock()
{

    return;
}

QblBlock::~QblBlock()
{

    return;
}

QblBlockBlob QblBlock::getRootDir()
{
    QblBlockBlob result;
    std::map<std::string, QblBlockBlob>::iterator iterator;

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (iterator->second.weight == WEIGHT_ROOT_ID) {
            return (iterator->second);
        }
    }

    std::string errmsg;
    errmsg = "Cannot find root directory";
    throw QblException { errmsg };

    return (result);
}

QblBlockBlob QblBlock::getDir(std::string hash)
{
    QblBlockBlob result;
    std::map<std::string, QblBlockBlob>::iterator iterator;

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (hash.compare(iterator->first)) {
            return (iterator->second);
        }
    }

    std::string errmsg;
    errmsg = "Cannot find directory";
    throw QblException { errmsg };

    return (result);
}

std::vector<char> QblBlock::getFileContent(std::string hash)
{
    std::vector<char> result;
    QblBlockTreeList::iterator iterator;

    for (iterator = this->tree.begin(); iterator != this->tree.end();
            iterator++) {
        if (! hash.compare(iterator->hash)) {
            return (std::vector<char>(iterator->startData,
                    iterator->startData + iterator->size));
        }
    }

    std::string errmsg;
    errmsg = "Cannot find file content";
    throw QblException { errmsg };

    return (result);
}

QblBlockTreeList QblBlock::getFilesFromDir(QblBlockBlob blob)
{
    QblBlockTreeList result;
    std::string str;
    size_t start;

    str = blob.text;

    if (str.find("[[\"") != 0 || str.find("\"]]") != str.size() - 3) {
        std::string errmsg;
        errmsg = "Blob entry is not a directory struct";
        throw QblException { errmsg };
    }

    start = 0;
    while (1) {
        size_t begin, end;
        std::string buffer;
        QblBlockTree tree;

        // find type
        begin = str.find("[\"", start);
        begin += 2;
        end = str.find("\",", begin);
        start = end;
        end -= begin;
        buffer = str.substr(begin, end);
        if (! buffer.compare(STR_TREE_FILE)) {
            tree.type = TYPE_FILE;
        } else if (! buffer.compare(STR_TREE_TREE)) {
            tree.type = TYPE_TREE;
        } else {
            std::string errmsg;
            errmsg = "Unknown file type";
            throw QblException { errmsg };
        }

        // find mode
        if (str[start++] != '"' || str[start++] != ',' || str[start++] != ' ') {
            throw QblException { "Error parsing archive header" };
        }
        begin = start;
        end = str.find(", ", begin);
        start = end;
        end -= begin;
        istringstream(str.substr(begin, end)) >> tree.mode;

        // find modification time
        if (str[start++] != ',' || str[start++] != ' ') {
            throw QblException { "Error parsing archive header" };
        }
        begin = start;
        end = str.find(", \"", begin);
        start = end;
        end -= begin;
        istringstream(str.substr(begin, end)) >> tree.modTime;

        // find file name
        begin = str.find(", \"", start);
        begin += 3;
        end = str.find("\", ", begin);
        start = end;
        end -= begin;
        tree.fileName = str.substr(begin, end);

        // find file name
        begin = str.find(", \"", start);
        begin += 3;
        end = str.find("\"]", begin);
        start = end;
        end -= begin;
        tree.hash = str.substr(begin, end);

        result.push_back(tree);

        if (str[start + 2] == ']') {
            break;
        }
    }

    return (result);
}

std::string QblBlock::convertModeToInt(mode_t mode)
{
    int iMode = 0, length = 4;
    char buffer[length];

#if 0
    if ((mode & S_ISUID) == S_ISUID) {
        iMode += INT_S_ISUID;
    }
    if ((mode & S_ISGID) == S_ISGID) {
        iMode += INT_S_ISGID;
    }
    if ((mode & S_ISVTX) == S_ISVTX) {
        iMode += INT_S_ISVTX;
    }
#endif
    if ((mode & S_IRUSR) == S_IRUSR) {
        iMode += INT_S_IRUSR;
    }
    if ((mode & S_IWUSR) == S_IWUSR) {
        iMode += INT_S_IWUSR;
    }
    if ((mode & S_IXUSR) == S_IXUSR) {
        iMode += INT_S_IXUSR;
    }
    if ((mode & S_IRGRP) == S_IRGRP) {
        iMode += INT_S_IRGRP;
    }
    if ((mode & S_IWGRP) == S_IWGRP) {
        iMode += INT_S_IWGRP;
    }
    if ((mode & S_IXGRP) == S_IXGRP) {
        iMode += INT_S_IXGRP;
    }
    if ((mode & S_IROTH) == S_IROTH) {
        iMode += INT_S_IROTH;
    }
    if ((mode & S_IWOTH) == S_IWOTH) {
        iMode += INT_S_IWOTH;
    }
    if ((mode & S_IXOTH) == S_IXOTH) {
        iMode += INT_S_IXOTH;
    }

    snprintf(buffer, length, "%.3d", iMode);

    return (std::string(buffer));
}

void QblBlock::build(std::string sourcePath)
{
    std::string rootId;
    QblBlockBlob blob;
    std::map<std::string, QblBlockBlob>::iterator iterator;

    rootId = this->hashTree(sourcePath);

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (!rootId.compare(iterator->first)) {
            iterator->second.weight = WEIGHT_ROOT_ID;
            break;
        }
    }

    return;
}

std::string QblBlock::hashTree(std::string sourcePath /*, blobs */)
{
    QblBlockTreeList list;
    DIR *dir;
    struct dirent *dirent;
    std::map<std::string, struct dirent *> dirents;
    std::map<std::string, struct dirent *>::iterator dirIt;
    std::list<std::string> files;
    std::list<std::string>::iterator iterator;
    QblBlockBlob blob;
    QblBlockResultListener *listener;
    QblSha256Digest digest;

    if ((dir = opendir(sourcePath.data())) == NULL) {
        std::string errmsg;
        errmsg = "Error open dir \"";
        errmsg += sourcePath;
        errmsg += "\"";
        std::string errorNumber = std::to_string(errno);
        std::string errorDesc(strerror(errno));
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    do {
        if ((dirent = readdir(dir)) != NULL) {
            std::string _path;
            QblBlockTree item;

            // TODO ignored files
            if (!strcmp(dirent->d_name, ".")) {
                continue;
            } else if (!strcmp(dirent->d_name, "..")) {
                continue;
            }

            item.fileName = dirent->d_name;

            _path.append(sourcePath);
            _path.append("/");
            _path.append(dirent->d_name);
            files.push_back(dirent->d_name);
            dirents.insert(
                    std::pair<std::string, struct dirent *>(dirent->d_name,
                            dirent));
        }
    } while (dirent != NULL);
    files.sort();
    for (iterator = files.begin(); iterator != files.end(); iterator++) {
        for (dirIt = dirents.begin(); dirIt != dirents.end(); dirIt++) {
            if (!dirIt->first.compare(*iterator)) {
                std::string _path;
                QblBlockTree item;
                struct stat _stat;
                struct tm *modTime;

                item.fileName = dirIt->second->d_name;

                _path.append(sourcePath);
                _path.append("/");
                _path.append(dirIt->second->d_name);

                switch (dirIt->second->d_type) {
                case DT_DIR:
                    item.type = TYPE_TREE;
                    item.hash = this->hashTree(_path.data());

                    if (stat(_path.data(), &_stat) == -1) {
                        std::string errmsg;
                        errmsg = "Cannot get stat for directory \"";
                        errmsg += _path;
                        errmsg += "\"";
                        throw QblException { errmsg };
                    }

                    modTime = gmtime(&(_stat.st_mtime));
                    item.modTime = mktime(modTime);
                    item.mode = _stat.st_mode;
                    list.push_back(item);
                    break;
                case DT_REG:
                    item.type = TYPE_FILE;
                    item.hash = this->hashFile(_path);
                    list.push_back(item);
                    break;
                default:
                    fprintf(stderr, "Unknown file type %d for file %s/%s\n", // DELETE 
                            dirent->d_type, sourcePath.data(), dirent->d_name);
                    break;
                }
            }
        }
    }

    (void) closedir(dir);

    blob.text = this->createTreeString(list);

    listener = new QblBlockResultListener();

    digest.init();
    digest.setListener(listener);
    digest.pushStr(blob.text);
    digest.finish();

    blob.hash = this->createHashString(listener->getResult());
    blob.weight = WEIGHT_TREE;

    this->addBlobToList(blob);

    return (blob.hash);
}

std::string QblBlock::hashFile(std::string path /*, blobs */)
{
    std::string result;
    std::ifstream file;

    file.open(path);
    if (file) {
        std::vector<char> buffer;
        std::streampos length;
        QblBlockResultListener *listener;
        QblSha256Digest digest;
        QblBlockBlob blob;

        file.seekg(0, std::ios::end);
        length = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(length);
        file.read(&buffer[0], length);
        file.close();

        listener = new QblBlockResultListener();

        digest.init();
        digest.setListener(listener);
        digest.push(buffer);
        digest.finish();
        result = this->createHashString(listener->getResult());

        blob.path = path;
        blob.hash = result;
        stat(blob.path.data(), &blob.stat);
        blob.weight = WEIGHT_FILE;

        this->addBlobToList(blob);
    }

    return (result);
}

std::string QblBlock::createHashString(std::string hashValue)
{
    char hashString[EVP_MAX_MD_SIZE * 2 + 1];

    for (unsigned int i = 0; i < hashValue.size(); i++) {
        snprintf(hashString + i * 2, 3, "%02x", hashValue[i] & 0xFF);
    }

    return (std::string(hashString));
}

void QblBlock::addBlobToList(QblBlockBlob blob)
{
    std::map<std::string, QblBlockBlob>::iterator iterator;

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (!blob.hash.compare((*iterator).first)) {
            return;
        }
    }

    this->blobs.insert(std::pair<std::string, QblBlockBlob>(blob.hash, blob));

    return;
}

std::string QblBlock::createTreeString(QblBlockTreeList list)
{
    std::string result;
    QblBlockTreeList::iterator iterator;
    std::map<std::string, QblBlockBlob>::iterator blobIt;

    result = "[";
    for (iterator = list.begin(); iterator != list.end(); iterator++) {
        int length = 20;
        struct tm *modTime;
        char buffer[length];
        bool foundOne = false;

        result.append("[\"");

        switch (iterator->type) {
        case TYPE_TREE:
            result.append(STR_TREE_TREE);
            result.append("\", ");
            result.append(QblBlock::convertModeToInt(iterator->mode));

            modTime = localtime(&iterator->modTime);
            strftime(buffer, length, "%s", modTime);
            result.append(", ").append(buffer);

            break;
        case TYPE_FILE:
            result.append(STR_TREE_FILE);
            result.append("\", ");

            for (blobIt = this->blobs.begin(); blobIt != this->blobs.end();
                    blobIt++) {
                if (! iterator->hash.compare(blobIt->first)) {
                    result.append(QblBlock::convertModeToInt(blobIt->second.stat.st_mode));

                    modTime = gmtime(&(blobIt->second.stat.st_mtime));
                    strftime(buffer, length, "%s", modTime);
                    result.append(", ").append(buffer);

                    foundOne = true;
                    break;
                }
            }

            if (foundOne == false) {
                std::string errmsg;
                errmsg = "Cannot find entry for file or directory \"";
                errmsg += iterator->fileName;
                errmsg += "\"";
                throw QblException { errmsg };
            }
            break;
        }

        result.append(", \"").append(iterator->fileName);
        result.append("\", \"").append(iterator->hash).append("\"], ");
    }

    // delete last comma if the string is >= 2
    if (result.size() < 2) {
      result.append("]");
    } else {
      result.resize(result.size() - 2);
    }

    return (result);
}

void QblBlock::writeInto(std::string key, std::vector<char> *buffer)
{
    this->writeIntoTree(WEIGHT_ROOT_ID, key, buffer);
    this->writeIntoTree(WEIGHT_TREE, key, buffer);
    this->writeIntoFile(key, buffer);

    return;
}

void QblBlock::writeIntoTree(int id, std::string key, std::vector<char> *buffer)
{
    std::map<std::string, QblBlockBlob>::iterator iterator;

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (iterator->second.weight == id) {
            std: string str;
            char c = 0;

            str.append(STR_TREE).append(iterator->second.hash.data());
            str.append(" ").append(to_string(iterator->second.text.size()));
            buffer->insert(buffer->end(), str.begin(), str.end());

            //buffer->insert(buffer->end(), '\0');
            buffer->insert(buffer->end(), c);

            str = iterator->second.text.data();
            buffer->insert(buffer->end(), str.begin(), str.end());
        }
    }

    return;
}

void QblBlock::writeIntoFile(std::string key, std::vector<char> *buffer)
{
    std::map<std::string, QblBlockBlob>::iterator iterator;

    for (iterator = this->blobs.begin(); iterator != this->blobs.end();
            iterator++) {
        if (iterator->second.weight == WEIGHT_FILE) {
            std::string str;
            std::ifstream file;
            char c = 0;

            str.append(STR_BLOB).append(iterator->second.hash.data());
            str.append(" ");
            str.append(to_string(iterator->second.stat.st_size));
            buffer->insert(buffer->end(), str.begin(), str.end());

            //buffer->insert(buffer->end(), '\0');
            buffer->insert(buffer->end(), c);

            // TODO file
            file.open(iterator->second.path, std::ios_base::binary);
            if (file) {
                int length;
                std::vector<char> content;
                QblBlockResultListener *listener;
                QblSha256Digest digest;
                std::string hash;
                std::vector<char>::iterator charIt;
                size_t current;

                length = iterator->second.stat.st_size;
                content.resize(length);
                file.read(&content[0], length);

                listener = new QblBlockResultListener();

                digest.init();
                digest.setListener(listener);
                digest.push(content);
                digest.finish();
                hash = this->createHashString(listener->getResult());

                if (hash.compare(iterator->first)) {
                    std::string errmsg;
                    errmsg = "File \"";
                    errmsg += iterator->second.path;
                    errmsg += "\" is changed while streaming";
                    std::string errorNumber = std::to_string(errno);
                    std::string errorDesc(strerror(errno));
                    throw QblException { errmsg, errorNumber, errorDesc };
                }

                current = buffer->size();
                charIt = buffer->begin();
                charIt += current;
                //buffer->resize(buffer->size() + iterator->second.stat.st_size);
                buffer->insert(buffer->end(), content.begin(), content.end());
                //buffer->append(content);
            } else {
                std::string errmsg;
                errmsg = "Error open file \"";
                errmsg += iterator->second.path;
                errmsg += "\"";
                std::string errorNumber = std::to_string(errno);
                std::string errorDesc(strerror(errno));
                throw QblException { errmsg, errorNumber, errorDesc };
            }
        }
    }

    return;
}

int QblBlock::parseHeader(std::vector<char>::iterator start, bool root)
{
    int retval = 0;
    std::vector<char> vector;
    std::vector<char>::iterator iterator, begin, end;
    std::string buffer;
    QblBlockBlob blob;
    size_t length;
    QblBlockResultListener *listener;
    QblSha256Digest digest;

    // get "tree"
    begin = start;
    end = begin + strlen(STR_TREE);
    buffer = std::string(begin, end);
    if (buffer.compare(STR_TREE)) {
        return (1);
    }

    // get checksum
    begin = end;
    end += HASH_LENGTH;
    blob.hash = std::string(begin, end);

    // search for \0 ...
    begin = end + 1;
    for (end; *end != 0; end++)
        ;
    // ... and get length
    istringstream(std::string(begin, end)) >> length;

    // get data
    begin = end + 1;
    end += length + 1;
    blob.text = std::string(begin, end);

    // check data
    listener = new QblBlockResultListener();

    digest.init();
    digest.setListener(listener);
    digest.push(std::vector<char>(begin, end));
    digest.finish();
    if (blob.hash.compare(this->createHashString(listener->getResult()))) {
        return (-1);
    }

    if (root == true) {
        blob.weight = WEIGHT_ROOT_ID;
    } else {
        blob.weight = WEIGHT_TREE;
    }
    this->blobs.insert(std::pair<std::string, QblBlockBlob>(blob.hash, blob));

    begin = end;
    this->startData = begin;

    this->parseHeader(begin, false);

    return (retval);
}

int QblBlock::parseData(std::vector<char>::iterator start)
{
    int result = 0;
    std::vector<char>::iterator iterator, begin, end;
    std::string buffer;
    QblBlockTree tree;
    QblBlockResultListener *listener;
    QblSha256Digest digest;

    // get "blob "
    begin = start;
    end = begin + strlen(STR_BLOB);
    buffer = std::string(begin, end);
    if (buffer.compare(STR_BLOB)) {
        return (1);
    }

    // get checksum
    begin = end;
    end += HASH_LENGTH;
    tree.hash = std::string(begin, end);

    // search for \0 ...
    begin = end + 1;
    for (end; *end != 0; end++)
        ;
    // ... and get length
    istringstream(std::string(begin, end)) >> tree.size;

    // get data
    begin = end + 1;
    tree.startData = begin;
    end += tree.size + 1;

    // check data
    listener = new QblBlockResultListener();

    digest.init();
    digest.setListener(listener);
    digest.push(std::vector<char>(begin, end));
    digest.finish();
    if (tree.hash.compare(this->createHashString(listener->getResult()))) {
        return (-1);
    }

    this->tree.push_back(tree);

    this->parseData(end);

    return (result);
}
