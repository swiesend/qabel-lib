/**
 * @file		qbl-curl.cpp
 * @brief		Class to send and receive web message using curl (Implementation)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl.h"
#include "qbl-curl.h"

QblCurl::QblCurl(std::string hostname, int port) :
    QblWeb(hostname, port), errorCode(-1)
{

    return;
}

int QblCurl::sendMessage(uint8_t *message, size_t length)
{
    return (-1);
}

int QblCurl::getErrorCode()
{
    return (this->errorCode);
}



int QblCurl::head(const char *uri)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::headModifiedSince(const char *uri, std::string time)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        struct curl_slist *header = NULL;

        std::string headercontent = "If-Modified-Since: ";
        headercontent.append(time);
        header = curl_slist_append(header, headercontent.c_str());

        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_slist_free_all(header);
        curl_easy_cleanup(curl);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::getModifiedSince(const char *uri, std::string time)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        struct curl_slist *header = NULL;

        std::string headercontent = "If-Modified-Since: ";
        headercontent.append(time);
        header = curl_slist_append(header, headercontent.c_str());

        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QblCurl::handleResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(header);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if (curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::get(const char *uri, const char *auth)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;
    if(this->response != NULL) {
        free (this->response);
    }

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        if (strlen(auth) > 0) {
            curl_easy_setopt(curl, CURLOPT_USERPWD, auth);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QblCurl::handleResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::post(const char *uri, const char *auth, const uint8_t *data,
        size_t length)
{
    return (this->postContentType(uri, auth, data, length, ""));
}

int QblCurl::postContentType(const char *uri, const char *auth,
        const uint8_t *data, size_t length, std::string contentType)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        struct curl_slist *header = NULL;
        std::string contentLength;

        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        if (strlen(auth) > 0) {
            curl_easy_setopt(curl, CURLOPT_USERPWD, auth);
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long )length);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QblCurl::handleResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        if (contentType.size() > 0) {
            header = curl_slist_append(header, contentType.data());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(header);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
        std::string errmsg;
        errmsg = "Cannot send data to server";
        std::string errorNumber = std::to_string(code);
        std::string errorDesc(curl_easy_strerror(code));
        throw QblException { errmsg, errorNumber, errorDesc };
    }

    return (this->errorCode);
}

int QblCurl::postFile(const char *uri, const char *auth, const uint8_t *data,
        size_t length)
{
    return (this->postContentType(uri, auth, data, length,
            "Content-Type: application/qabel"));
}

int QblCurl::postJson(const char *uri, const char *auth, const uint8_t *data,
        size_t length)
{
    return (this->postContentType(uri, auth, data, length,
            "Content-Type: application/json"));
}

int QblCurl::del(const char *uri, const char *auth = "",
        std::string contentType = "")
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        // Now set up all of the curl options
        struct curl_slist *header = NULL;

        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());

        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        if (strlen(auth) > 0) {
            curl_easy_setopt(curl, CURLOPT_USERPWD, auth);
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QblCurl::handleResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        if (contentType.size() > 0) {
            header = curl_slist_append(header, contentType.data());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::put(const char *uri, const char *auth, const uint8_t *data,
        size_t length)
{
    return (this->putContentType(uri, auth, data, length, ""));
}

int QblCurl::putContentType(const char *uri, const char *auth,
        const uint8_t *data, size_t length, std::string contentType)
{
    CURL *curl;
    CURLcode code;
    struct data buffer;

    buffer.length = 0;
    buffer.data = NULL;

    // Create our curl handle
    curl = curl_easy_init();

    char errorBuffer[CURL_ERROR_SIZE];
    // Write all expected data in here

    if (curl) {
        struct curl_slist *header = NULL;
        std::string contentLength;

        contentLength = "Content-Length: ";
        contentLength.append(to_string(length));

        header = curl_slist_append(header, contentLength.data());

        // Now set up all of the curl options
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, this->createUrl(uri).data());
        if (strlen(auth) > 0) {
            curl_easy_setopt(curl, CURLOPT_USERPWD, auth);
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long )length);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QblCurl::handleResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        if (contentType.size() > 0) {
            header = curl_slist_append(header, contentType.data());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

        // Attempt to retrieve the remote page
        code = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(header);
    }

    if (code == CURLE_OK) {
        long errorCode;

        this->response = (uint8_t *) malloc(buffer.length * sizeof(uint8_t));
        if (this->response == NULL) {
            return (-1);
        }
        memcpy(this->response, buffer.data, buffer.length);
        this->responseSize = buffer.length;
        free(buffer.data);
        if ( curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &errorCode)
                == CURLE_OK) {
            this->errorCode = (int) errorCode;
        }
    } else {
        this->errorCode = -1;
    }

    return (this->errorCode);
}

int QblCurl::putJson(const char *uri, const char *auth, const uint8_t *data,
        size_t length)
{
    return (this->putContentType(uri, auth, data, length,
            "Content-Type: application/json"));
}

int QblCurl::handleResponse(char *data, size_t size, size_t nmemb, void *buffer)
{
    
    
    struct data *_buffer = (struct data *) buffer;
    uint8_t *__buffer;

    _buffer->data = (uint8_t *) realloc(_buffer->data,
            (_buffer->length + nmemb) * size);
    if (buffer == NULL) {
        return (0);
    }
    __buffer = _buffer->data;
    __buffer += _buffer->length;

    memcpy(__buffer, data, size * nmemb);

    _buffer->length += nmemb;

    return (size * nmemb);
}

std::string QblCurl::createUrl(std::string uri)
{
    std::string result;

    result = this->getHostname();
    result.append(":").append(std::to_string(this->getPort())).append("/").append(
            uri);

    return (result);
}

std::string QblCurl::getResponseString()
{
    uint8_t *data = getResponse();
    if (getResponseSize() > 0) {
        std::string response((char *)getResponse(), getResponseSize());
        return response;
    } else
        return "no response received";
}
