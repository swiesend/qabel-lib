/**
 * @file		qbl-web.h
 * @brief		Class to send and receive web message (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#ifndef __QBL_WEB_H__
#define __QBL_WEB_H__

#include "qbl-net.h"

 /**
  * Class QblWeb: Class to send and receive web message
  */
class QblWeb: public QblNet {
public:
	/**
	 * Constructor
	 * @param hostname Name of the server host
	 * @param port Port to use
	 */
    QblWeb(std::string hostname, int port);
    /**
     * Destructor
     */
    virtual ~QblWeb();

    /**
     * Get the return value of the HTTP communication
     * @return HTTP return value or -1 if there was no communication
     */
    int getErrorCode();
    /**
     * Return the time stamp of the received message (server time)
     * @return Time Stamp
     */
	const std::string& getDate() const;
    /**
     * Check the received message
     */
    void checkResponse();

private:
    int errorCode;					/**< Received error code */
    std::string date;				/**< Date of the received message */

   
};

#endif /* __QBL_WEB_H__ */
