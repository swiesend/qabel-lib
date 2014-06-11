/*
 * @file		qbl-block-result-listener.cpp
 * @brief		Listener of the hash values for the block stuff (Implementation)
 * @author		Michael Ott <ott@qabel.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-block-result-listener.h"

QblBlockResultListener::~QblBlockResultListener()
{

    return;
}

void QblBlockResultListener::onData(const std::vector<char>&data)
{
    this->result = std::string(data.begin(), data.end());

    return;
}

void QblBlockResultListener::onFinish()
{

    return;
}

std::string QblBlockResultListener::getResult()
{
    return (this->result);
}
