/*
 * @file		qbl-block-result-listener.h
 * @brief		Listener of the hash value for the block stuff (Header file)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_BLOCK_RESULT_LISTENER_H__
#define __QBL_BLOCK_RESULT_LISTENER_H__

#include <vector>
#include <string>

#include "qbl-pipe.h"

/**
 * Class QblBlockResultListener: Listener of the hash value for the block stuff
 */
class QblBlockResultListener : public QblPipeListener {
public:
    /**
     * Destructor
     */
    virtual ~QblBlockResultListener();

    /**
     * New data available and have to handle
     * @param data New data
     */
    void onData(const std::vector<char>&data);
    /**
     * All data received
     */
    void onFinish();
    /**
     * Get received data
     * @return
     */
    std::string getResult();

private:
    std::string result;             //!< Received data
};

#endif   // __QBL_BLOCK_RESULT_LISTENER_H__
