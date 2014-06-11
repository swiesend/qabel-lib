/*
 * @file		qbl-block-upload.h
 * @brief		Class to upload files (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_BLOCK_UPLOAD_H__
#define __QBL_BLOCK_UPLOAD_H__

#include "qbl-block.h"
#include "qbl-json-main-config-share.h"
#include "qbl-json-main-config-upload.h"
#include "qbl-json-main-config-blockserver.h"
#include "iqbl-chat-send.h"

/**
 * Class QblBlockUpload: Class to upload files (Header file)
 */
class QblBlockUpload : public QblBlock, IQblChatSend {
public:
    /**
     * Constructor
     * @param share Configuration about the share
     */
    QblBlockUpload(QblJsonMainConfigShare *share);
    virtual ~QblBlockUpload();
    /**
     * Pack the directory or file
     */
    void pack();
    /**
     * Pack the directory or file
     * TODO to delete when the right test is working
     * @param sourcePath Source file or path
     * @param key Encryption key
     * @param url URL of the blob server
     * @param outputPath File to which the sources shall packed
     */
    void pack(std::string sourcePath, std::string key, std::string url,
            std::string outputPath);
    /**
     * Message is send to the other side
     * @param done true == Message is sent
     */
    void messageSend(bool done);

private:
    QblJsonMainConfigShare *share;
    QblJsonMainConfigBlockServer *server;
    QblJsonMainConfigUpload *upload;




};

#endif /* __QBL_BLOCK_UPLOAD_H__ */
