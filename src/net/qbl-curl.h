/**
 * @file		qbl-curl.h
 * @brief		Class to send and receive web message using curl (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_CURL_H__
#define __QBL_CURL_H__

#include <stddef.h>
#include <cstdint>
#include <string>
#include <curl/curl.h>
#include <string.h>
#include <iostream>

#include "qbl-web.h"

#define CONTENT_TYPE_FORM_URL "application/x-www-form-urlencoded"
/**
 * Class QblCurl: Class to send and receive web message using curl
 */
class QblCurl: public QblWeb {
public:
    /**
     * Struct to handle received data from server
     */
    struct data {
        uint8_t *data; /**< Received data */
        size_t length; /**< Length of the received data */
    };

    /**
     * Constructor
     * @param hostname Name of the server host
     * @param port Port to use
     */
    QblCurl(std::string hostname, int port);

    /**
     * Send message to server
     * @param message Message to send
     * @param length Length of the message
     * @return 0 == successful
     */
    int sendMessage(uint8_t *message, size_t length);
    /**
     * Get the return value of the HTTP communication
     * @return HTTP return value or -1 if there was no communication
     */
    int getErrorCode();
    /**
     * head message from server
     * @param uri URO to ask for
     * @return Error code or -1 if something failed
     */
    int head(const char *uri);
    /**
     * headModifiedSince message from server
     * head message with Modified Since header from server
     * @param uri  URI to ask for
     * @return Error code or -1 if something failed
     */
    int headModifiedSince(const char *uri, std::string time);
    /**
     * getModoifiedSince message from server
     * @param uri URI to ask for
     * @return Error code or -1 if something failed
     */
    int getModifiedSince(const char *uri, std::string);
    /**
     * Get message from server
     * @param uri URI to ask for
     * @param authentication credentials
     * @return Error code or -1 if something failed
     */
    int get(const char *uri, const char *auth);
    /**
     * Post data to server
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @return Error code or -1 if something failed
     */
    int post(const char *uri, const char *auth, const uint8_t *data,
            size_t length);
    /**
     * Post data to server using a specified content type
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @param contentType Content type with key
     * @return Error code or -1 if something failed
     */
    int postContentType(const char *uri, const char *auth, const uint8_t *data,
            size_t length, std::string contentType = CONTENT_TYPE_FORM_URL);
    /**
     * Post content of a file to server
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @return Error code or -1 if something failed
     */
    int postFile(const char *uri, const char *auth, const uint8_t *data,
            size_t length);
    /**
     * Post json object to server
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @return Error code or -1 if something failed
     */
    int postJson(const char *uri, const char *auth, const uint8_t *data,
            size_t length);
    /**
     * Delete message from server
     * @param authentication credentials
     * @param uri URI to ask for
     * @return Error code or -1 if something failed
     */
    int del(const char *uri, const char *auth, std::string contentType);
    /**
     * Put data to server
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @return Error code or -1 if something failed
     */
    int put(const char *uri, const char *auth, const uint8_t *data,
            size_t length);
    /**
     * Put data to server using a specified content type
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @param contentType Content type with key
     * @return Error code or -1 if something failed
     */
    int putContentType(const char *uri, const char *auth, const uint8_t *data,
            size_t length, std::string contentType = CONTENT_TYPE_FORM_URL);
    /**
     * Put json object to server
     * @param uri URI to ask for
     * @param authentication credentials
     * @param data Data to send
     * @param length Length of the data
     * @return Error code or -1 if something failed
     */
    int putJson(const char *uri, const char *auth, const uint8_t *data,
            size_t length);
    /**
     * Handle response from server
     * @param data Received data
     * @param size Size of one element
     * @param nmemb Size of the data
     * @param buffer Buffer to which the data shall copied
     * @return Complete length of received data
     */
    static int handleResponse(char *data, size_t size, size_t nmemb,
            void *buffer);

    /**
     * @brief getResponseString
     * @return
     */
    std::string getResponseString();

private:
    int errorCode; /**< Received error code */

    /**
     * Create complete URL
     * @param uri URI to use
     * @return URL
     */
    std::string createUrl(std::string uri);
};

#endif /* __QBL_CURL_H__ */
