/*
 * @file		qbl-json-main-config-preferences.cpp
 * @brief		Class to handle the preferences in the main configuration (Implementation)
 * @author		Fabian Träger <traeger@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "qbl-json.h"
#include "qbl-json-main-config-preferences.h"

QblJsonMainConfigPreferences::QblJsonMainConfigPreferences() :
        QblJson()
{

    return;
}

QblJsonMainConfigPreferences::~QblJsonMainConfigPreferences()
{
    int i;

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (this->elements[i].type == json_type_string) {
            delete ((std::string *) this->elements[i].obj);
        }
        else if (this->elements[i].type == json_type_boolean) {
            delete ((bool *) this->elements[i].obj);           
        }
        else if (this->elements[i].type == json_type_int) {
            delete ((int *) this->elements[i].obj);
        }
        else if(this->elements[i].type == json_type_double) {
            delete ((double *) this->elements[i].obj);
        }
    }

    return;
}

void QblJsonMainConfigPreferences::parse(std::string string)
{
    QblJson::parse(string);

    this->parse();

    return;
}

void QblJsonMainConfigPreferences::parse(json_object *obj)
{
int i;
    bool foundOne;

    if (obj != NULL) {
        this->obj = obj;
    }

    json_object_object_foreach(this->obj, key, value) {
        foundOne = false;
        for (i = 0;
                i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
                i++) {
            if (strcmp(this->elements[i].name, key)) {
                continue;
            }
            foundOne = true;

            if (this->elements[i].checked == true) {
                throw QblJsonException("Element \"%s\" already exists\n", key);
            }
            if (this->elements[i].type != json_object_get_type(value)) {
                throw QblJsonException("Element \"%s\" have wrong type\n", key);
            }
            this->elements[i].checked = true;
            if(this->elements[i].type == json_type_string) {
                ((std::string *) this->elements[i].obj)->append(
                    json_object_get_string(value));
            }
            else if(this->elements[i].type == json_type_boolean) {
                this->elements[i].obj = new bool(json_object_get_boolean(value));
            }
            else if(this->elements[i].type == json_type_int) {
                this->elements[i].obj = new int(json_object_get_int(value));
            }
            else if(this->elements[i].type == json_type_double) {
                this->elements[i].obj = new double(json_object_get_double(value));
            }


            break;
        }

        if (foundOne == false) {
            bool retval;

            retval = QblJsonObject::parse(key, value);
            if (retval == false) {
                throw QblJsonException("Element \"%s\" is not allowed here\n",
                        key);
            }
        }
    }


    /**
     * Check whether everything is set
     */
    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        if (this->elements[i].checked == false) {
            throw QblJsonException("Element \"%s\" is missing\n",
                    this->elements[i].name);
        }
    }

    return;
}

std::string QblJsonMainConfigPreferences::getJsonString()
{
    std::string result;
    int i;
    result += QblJson::getJsonString();

    for (i = 0; i < (int) (sizeof(this->elements) / sizeof(this->elements[0]));
            i++) {
        result += "\n\t\t";
        result += QblJson::getJsonString(&this->elements[i]);
        result += ",";
    }

    // Remove last comma
    result = result.substr(0, result.size() - 1);
    result += "\n\t";
    return (result);
}

void QblJsonMainConfigPreferences::integrate(QblJson* other)
{
    QblJsonObject::integrate(other);

    this->setUseWebSockets(((QblJsonMainConfigPreferences *)other)->getUseWebSockets());
    this->setDefaultPollInterval(((QblJsonMainConfigPreferences *)other)->getDefaultPollInterval());
    this->setStartMinimized(((QblJsonMainConfigPreferences *)other)->getStartMinimized());
    this->setFFsyncUrl(((QblJsonMainConfigPreferences *)other)->getFFsyncUrl());
    this->setFFsyncAuth(((QblJsonMainConfigPreferences *)other)->getFFsyncAuth());
    this->setDesktopX(((QblJsonMainConfigPreferences *)other)->getDesktopX());
    this->setDesktopY(((QblJsonMainConfigPreferences *)other)->getDesktopY());
    this->setDesktopWidth(((QblJsonMainConfigPreferences *)other)->getDesktopWidth());
    this->setDesktopHeight(((QblJsonMainConfigPreferences *)other)->getDesktopHeight());
    return;
}

bool QblJsonMainConfigPreferences::getUseWebSockets() const {
    return (*((bool*) this->elements[USE_WEBSOCKETS].obj));
}

void QblJsonMainConfigPreferences::setUseWebSockets(const bool value) {
    *((bool*)this->elements[USE_WEBSOCKETS].obj) = value;
}

int QblJsonMainConfigPreferences::getDefaultPollInterval() const {
    return (*((int*) this->elements[DEFAULT_POLL_INTERVAL].obj));
}

void QblJsonMainConfigPreferences::setDefaultPollInterval (const int value) {
    *((int*)this->elements[DEFAULT_POLL_INTERVAL].obj) = value;
}

bool QblJsonMainConfigPreferences::getStartMinimized() const {
    return (*((bool*) this->elements[START_MINIMIZED].obj));
}

void QblJsonMainConfigPreferences::setStartMinimized(const bool value) {
    *((bool*)this->elements[START_MINIMIZED].obj) = value;
}

const std::string& QblJsonMainConfigPreferences::getFFsyncUrl() const{
    return (*((std::string *) this->elements[FFSYNC_URL].obj));
}

void QblJsonMainConfigPreferences::setFFsyncUrl(const std::string& ffsyncUrl) {
    if(this->elements[FFSYNC_URL].obj != &ffsyncUrl) {
        ((std::string *)this->elements[FFSYNC_URL].obj)->clear();
        ((std::string *)this->elements[FFSYNC_URL].obj)->append(ffsyncUrl);
    }
    return;
}

const std::string& QblJsonMainConfigPreferences::getFFsyncAuth() const{
    return (*((std::string *) this->elements[FFSYNC_AUTH].obj));
}

void QblJsonMainConfigPreferences::setFFsyncAuth(const std::string& ffsyncAuth) {
    if(this->elements[FFSYNC_AUTH].obj != &ffsyncAuth) {
        ((std::string *)this->elements[FFSYNC_AUTH].obj)->clear();
        ((std::string *)this->elements[FFSYNC_AUTH].obj)->append(ffsyncAuth);
    }
    return;
}

const std::string& QblJsonMainConfigPreferences::getDesktopX() const{
    return (*((std::string *) this->elements[DESKTOP_X].obj));
}

void QblJsonMainConfigPreferences::setDesktopX(const std::string& desktopX) {
    if(this->elements[DESKTOP_X].obj != &desktopX) {
        ((std::string *)this->elements[DESKTOP_X].obj)->clear();
        ((std::string *)this->elements[DESKTOP_X].obj)->append(desktopX);
    }
    return;
}

const std::string& QblJsonMainConfigPreferences::getDesktopY() const{
    return (*((std::string *) this->elements[DESKTOP_Y].obj));
}

void QblJsonMainConfigPreferences::setDesktopY(const std::string& desktopY) {
    if(this->elements[DESKTOP_Y].obj != &desktopY) {
        ((std::string *)this->elements[DESKTOP_Y].obj)->clear();
        ((std::string *)this->elements[DESKTOP_Y].obj)->append(desktopY);
    }
    return;
}

const std::string& QblJsonMainConfigPreferences::getDesktopWidth() const{
    return (*((std::string *) this->elements[DESKTOP_WIDTH].obj));
}

void QblJsonMainConfigPreferences::setDesktopWidth(const std::string& desktopWidth) {
    if(this->elements[DESKTOP_WIDTH].obj != &desktopWidth) {
        ((std::string *)this->elements[DESKTOP_WIDTH].obj)->clear();
        ((std::string *)this->elements[DESKTOP_WIDTH].obj)->append(desktopWidth);
    }
    return;
}

const std::string& QblJsonMainConfigPreferences::getDesktopHeight() const{
    return (*((std::string *) this->elements[DESKTOP_HEIGHT].obj));
}

void QblJsonMainConfigPreferences::setDesktopHeight(const std::string& desktopHeight) {
    if(this->elements[DESKTOP_HEIGHT].obj != &desktopHeight) {
        ((std::string *)this->elements[DESKTOP_HEIGHT].obj)->clear();
        ((std::string *)this->elements[DESKTOP_HEIGHT].obj)->append(desktopHeight);
    }
    return;
}
