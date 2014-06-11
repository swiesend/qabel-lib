/**
 * @file		messages.cpp
 * @brief		Example for system tray messages
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

#include <list>
using namespace std;

#include <stdio.h>

#include "qbl.h"
#include "qbl-json.h"

class JsonRead: public QblJson {
public:
    JsonRead() :
            QblJson()
    {
        return;
    }

    ~JsonRead()
    {
    }

    void parse(std::string string)
    {
        QblJson::parse(string);

        this->parse();

        return;
    }

    void parse(json_object *obj = NULL)
    {
        if (obj != NULL) {
            this->obj = obj;
        }

        run_through(this->obj, 1);

        return;
    }

    std::string getJsonString()
    {

        return (NULL);
    }

    void integrate(QblJson* other)
    {

        return;
    }

private:
    void run_through(json_object * obj, int deepth)
    {
        enum json_type type;
        int i;

        json_object_object_foreach(obj, key, val) {
            for (i = 0; i < deepth; i++) {
            }

            type = json_object_get_type(val);
            switch (type) {
            case json_type_null:
                break;
            case json_type_boolean:
                break;
            case json_type_double:
                break;
            case json_type_int:
                break;
            case json_type_object:
                run_through(val, deepth + 1);
                break;
            case json_type_array:
                run_through_array(val);
                break;
            case json_type_string:
                break;
            }
        }

        return;
    }

    void run_through_array(json_object * obj)
    {
        int i, length;
        json_object *value;

        length = json_object_array_length(obj);
        for (i = 0; i < length; i++) {
            value = json_object_array_get_idx(obj, i);
        }
        return;
    }

};

int main(void)
{
    std::string string =
            "{"
                    "\"sitename\" : \"joys of programming\","
                    " \"tags\" : [ \"c\" , \"c++\", \"java\", \"PHP\" ],"
                    " \"author-details\": { \"name\" : \"Joys of Programming\", \"Number of Posts\" : 10 },"
                    "\"price\" : 7.99," "\"orderable\" : true," " }";
    JsonRead *json;
    int i;

    json = new JsonRead();
    json->parse(string);

    delete (json);

    return 0;
}
