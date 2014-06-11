#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
#include <iostream>
std::string userId("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string url("http://praecloud.prae.local");
std::string newUser("frxws6yaqktbbwov5ewntzxjtswsdxmf");
int port = 5000;
std::string path("addons");

using namespace std;

SCENARIO( "Create User"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(newUser, password, url, port);

        WHEN( "A string is pushed into the object and gets returned as hash" ){
            std::string result = user->createUser("q@qq.de");
            THEN( "Result should be 1"){
                REQUIRE(result == newUser);
            }
        }
    }
}
