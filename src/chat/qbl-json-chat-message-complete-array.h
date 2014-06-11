/*
 * @file		qbl-json-chat-message-complete-array.h
 * @brief		Class to handle an array of complete chat messages (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_JSON_CHAT_MESSAGE_COMPLETE_ARRAY_H__
#define __QBL_JSON_CHAT_MESSAGE_COMPLETE_ARRAY_H__

#include <list>
#include <string>

#include "qbl-json-chat-message-complete.h"
#include "qbl-json-array.h"

using namespace std;

/**
 * class
 * @brief		Class to handle the chat messages (Header file)
 */
class QblJsonChatMessageCompleteArray : public QblJsonArray {
public:
    /**
     * Constructor
     */
    QblJsonChatMessageCompleteArray();
    /**
     * Destructor
     */
    virtual ~QblJsonChatMessageCompleteArray();

    /**
     * Function to parse the JSON string
     * @return true == everything okay
     */
    void parse(std::string string);
    /**
     * Function to parse the JSON object
     * @param obj Object to parse
     * @return
     */
    void parse(json_object *obj = NULL);
    /**
     * Get JSON object
     * @return JSON string
     */
    std::string getJsonString();
    /**
     * Integrate the other JSON object into the existing
     * @param other Object to integrate
     */
    void integrate(QblJson *other);

    /**
     * Get the list of all found elements
     * @return
     */
    std::list<QblJsonChatMessageComplete *> getList();

private:

};

#endif /* __QBL_JSON_CHAT_MESSAGE_COMPLETE_ARRAY_H__ */
