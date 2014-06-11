/*
 * @file		qbl-block.h
 * @brief		Main class for the up- and download of files (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_BLOCK_H__
#define __QBL_BLOCK_H__

#include <sys/stat.h>

#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

#define WEIGHT_ROOT_ID 1
#define WEIGHT_TREE 3
#define WEIGHT_FILE 4

/**
 * Struct to save the information about the file or save
 */
struct _QblBlockBlob {
    std::string hash;               //!< Hash value in hex form
    std::string text;               //!< JSON information about a directory
    std::string path;               //!< File name
    struct stat stat;               //!< Information of a file
    int weight;                     //!< Weight of the entry
};
typedef struct _QblBlockBlob QblBlockBlob;
/**
 * enum to identify the type of the file
 */
enum _QblBlockFileType {
    TYPE_FILE,                      //!< TYPE_FILE Entry is a file
    TYPE_TREE                       //!< TYPE_TREE Entry is a directory
};
typedef enum _QblBlockFileType QblBlockFileType;
/**
 * Struct to create a "JSON" entry of an element
 */
struct _QblBlockTree {
    QblBlockFileType type;          //!< Type of the file
    std::string fileName;           //!< Name of the file
    std::string hash;               //!< Hash value of the file in hex form
    size_t size;                    //!< Size of the file or 0
    mode_t mode;                    //!< Mode of the file
    time_t modTime;                 //!< Last modification
    std::vector<char>::iterator startData; //!< start iterator
};
typedef struct _QblBlockTree QblBlockTree;
typedef std::list<QblBlockTree> QblBlockTreeList;

/**
 * Class QblBlock: Main class for the up- and download of files
 */
class QblBlock {
public:

    /**
     * Constructor
     * TODO add authentification
     */
    QblBlock();
    /**
     * Destructor
     */
    virtual ~QblBlock();

    /**
     * Get root directory
     * @return Blob struct entry of the root directory
     */
    QblBlockBlob getRootDir();
    /**
     * Get directory
     * @param hash Hash value of the directory
     * @return Blob struct entry of the directory
     */
    QblBlockBlob getDir(std::string hash);
    /**
     * Get file content
     * @param hash Hash value of the file
     * @return File content
     */
    std::vector<char> getFileContent(std::string hash);
    /**
     * Get files entry from blob as a list
     * @param blob Blob struct entry of the directory
     * @return List of files of the directory
     */
    static QblBlockTreeList getFilesFromDir(QblBlockBlob blob);
    /**
     * Convert the file mode to a "octal" output
     * @param mode Mode to convert
     * @return "Octal" output
     */
    static std::string convertModeToInt(mode_t mode);

protected:
    std::map<std::string, QblBlockBlob> blobs; /**< Map of all blobs */
    QblBlockTreeList tree;          /**< List of all tree entries */
    std::vector<char> data;         /**< Uncompressed data */
    std::vector<char>::iterator startData; /**< Start iterator of the data */

    /**
     * Build the blob entries for the sources
     * @param sourcePath Source file or path
     */
    void build(std::string sourcePath);
    /**
     * Create blob entry for a tree
     * @param sourcePath Source path to create a blob entry
     * @return Hash key
     */
    std::string hashTree(std::string sourcePath);
    /**
     * Create blob entry for a file
     * @param path Source path to create a blob entry
     * @return Hash key
     */
    std::string hashFile(std::string path);
    /**
     * Create a readable hash string from the hash value
     * @param hashValue Hash value in normal form
     * @return Hash string in hex form
     */
    static std::string createHashString(std::string hashValue);
    /**
     * Add blob to blob map if not already added
     * @param blob Blob to add
     */
    void addBlobToList(QblBlockBlob blob);
    /**
     * Create tree string of tree list
     * @param list Tree list to convert
     * @return tree string
     */
    std::string createTreeString(QblBlockTreeList list);
    /**
     * Transform block info
     * @param key Key to encrypt data
     * @param buffer Buffer to write block information
     */
    void writeInto(std::string key, std::vector<char> *buffer);
    /**
     * Transform block info for a tree
     * @param id Weight id
     * @param key Key to encrypt data
     * @param buffer Buffer to write block information
     */
    void writeIntoTree(int id, std::string key, std::vector<char> *buffer);
    /**
     * Transform block info for a file
     * @param key Key to encrypt data
     * @param buffer Buffer to write block information
     */
    void writeIntoFile(std::string key, std::vector<char> *buffer);
    /**
     * Parse the header of the decompressed data
     * @param start Start point of the next data
     * @param root Is this the root directory?
     * @return 0 == successful; 1 == no tree; < 0 == error
     */
    int parseHeader(std::vector<char>::iterator start, bool root = true);
    /**
     * Parse the header of the decompressed data
     * @param start Start point of the next data
     * @return 0 == successful; 1 == no tree; < 0 == error
     */
    int parseData(std::vector<char>::iterator start);

};

#endif /* __QBL_BLOCK_H__ */
