 /*
 * @file		qbl-config-file.h
 * @brief		Class which handle the directory and file stuff (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CONFIG_FILE_H__
#define __QBL_CONFIG_FILE_H__

#include <string>
using namespace std;

#include "qbl-main-config.h"

/**
 * Class QblConfigFile: Class which handle the directory and file stuff
 */
class QblConfigFile {
public:
	/**
	 * Constructor
	 */
	QblConfigFile();
	/**
	 * Destructor
	 */
	virtual ~QblConfigFile();

    /**
     * Return the home directory
     * @todo check whether is function runs on Android and MAC
     * @return Home directory
     */
    static const char *getHomeDir();
    /**
     * Return the user chat cache directory
     * @return User chat cache directory
     */
    static std::string getCacheChatDir();
    /**
     * Read the default JSON config file
     * @todo handle encrypted configuration and send callback for
     * @return
     */
    int readConfigFile(QblMainConfig **config);
    
    static std::string getConfigFileName();

private:
    std::string cacheChatDir;		/**< Default cache folder for chat
                                      messages */

    /**
     * Create directory
     */
    int createDir(std::string path);
    /**
     * Create user config directory
     */
    int createConfigDir();
    /**
     * Create user config directory
     */
    int createCacheDir();
    /**
     * Return the directory where the config is
     * @todo check whether is function runs on Android and MAC
     * @return Config directory
     */
    static const char *getConfigDir();
    /**
     * Return the directory where the cache files are
     * @todo check whether is function runs on Android and MAC
     * @return Config directory
     */
    static const char *getCacheDir();

};

#endif /* __QBL_CONFIG_FILE_H__ */
