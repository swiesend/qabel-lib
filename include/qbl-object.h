/*
 * @file		qbl-object.h
 * @brief		Main Class to handle object in the library (Header file)
 * @author		Michael Ott <michael@king-coder.de>
 *
 * copyright:	(C) 2014 by Qabel GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __QBL_OBJECT_H__
#define __QBL_OBJECT_H__

/**
 * QblObject: Main Class to handle object in the library
 */
class QblObject {
public:
	/**
	 * Type of this object
	 */
	enum type {
		CHAT,						//!< CHAT Chat object
	};
    /**
     * Constructor
     */
    QblObject(QblObject::type type) :  type(type) {};
    /**
     * Destructor
     */
	virtual ~ QblObject()
	{
	}

	/**
	 * Get sending counter
	 * @return Number of try to send object
	 */
	int getCounter() const
	{
		return counter;
	}

	/**
	 * Get type of the object
	 * @return Type of the object
	 */
	enum type getType() const
	{
		return type;
	}

protected:
    int counter;					//!< How often is it try to send

private:
    enum type type;					//!< Type of the object
};

#endif                          /* __QBL_OBJECT_H__ */
