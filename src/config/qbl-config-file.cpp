 /*
  * @file       qbl-config-file.cpp
  * @brief      Class which handle the directory and file stuff (Implementation)
  * @author     Michael Ott <michael@king-coder.de>
  *
  * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

// TODO Compiler switch for Android and / or Mac
#include <glib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
/**
#include <stdlib.h>
*/

#include "qbl-config-file.h"
#include "qbl.h"

#define CONFIG_DIR "qabel"
#define JSON_CONFIG_FILE  "config.json"

QblConfigFile::QblConfigFile()
{
    // TODO Auto-generated constructor stub

    return;
}

QblConfigFile::~QblConfigFile()
{

    return;
}

std::string QblConfigFile::getCacheChatDir()
{
    std::string str;

    str.append(QblConfigFile::getCacheDir()).append("/").append(CONFIG_DIR)
        .append("/").append("chat");

    return(str);
}


std::string QblConfigFile::getConfigFileName()
{
    std::string fileName;
    fileName.append(getConfigDir()).append("/").append(CONFIG_DIR)
        .append("/").append(JSON_CONFIG_FILE);
    return fileName;
}

int QblConfigFile::readConfigFile(QblMainConfig ** config)
{
    int retval;
    struct stat _stat;
    std::string str;
    std::string fileName;

    fileName = QblConfigFile::getConfigFileName();

    retval = this->createConfigDir();
    if (retval != 0) {
        return (retval);
    }
    retval = this->createCacheDir();
    if (retval != 0) {
        return (retval);
    }

    *config = new QblMainConfig(fileName);

    return (0);
}

int QblConfigFile::createDir(std::string path)
{
    int retval;
    struct stat _stat;

    retval = stat(path.data(), &_stat);
    if (retval != 0) {
        // create config directory
        if (errno == ENOENT) {
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
            retval = mkdir(path.data());
#else
            retval = mkdir(path.data(), 0700);
#endif
            if (retval != 0) {
                return (-errno);
            }
        } else {
            return (-errno);
        }
    }

    return (0);
}

int QblConfigFile::createConfigDir()
{
    std::string path;

    path.append(this->getConfigDir()).append("/").append(CONFIG_DIR);

    return (this->createDir(path));
}

int QblConfigFile::createCacheDir()
{
    std::string path, path2;
    int retval;

    path.append(this->getCacheDir()).append("/").append(CONFIG_DIR)
        .append("/");
    retval = this->createDir(path);
    if (retval != 0) {
        return (retval);
    }
    // TODO add the other directory that is needed
    this->cacheChatDir = path;
    this->cacheChatDir.append("chat");
    retval = this->createDir(this->cacheChatDir);
    if (retval != 0) {
        return (retval);
    }

    return (0);
}

const char* QblConfigFile::getHomeDir()
{
    return (g_get_home_dir());
}

const char *QblConfigFile::getConfigDir()
{
    return (g_get_user_config_dir());
}

const char *QblConfigFile::getCacheDir()
{
    return (g_get_user_cache_dir());
}
