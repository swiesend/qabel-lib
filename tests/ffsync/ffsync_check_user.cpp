#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"

std::string userIdExist("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string userIdDoesNotExist("z6v4uyloivun7qtfbsmu7biufkbnwp44");
std::string url("http://praecloud.prae.local:5000");

using namespace std;

SCENARIO( "User exists"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(userIdExist,password,url);

        WHEN( "A string is pushed into the object and gets returned as hash" ){
            user->checkUser();
            string result = user->getResponse();

            THEN( "Result should be 1"){
                REQUIRE(strcmp(result.c_str(), "1"));
            }
        }
    }
}
SCENARIO( "User does not exist"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(userIdDoesNotExist,password,url);

        WHEN( "A string is pushed into the object and gets returned as hash" ){
            user->checkUser();
            string result = user->getResponse();

            THEN( "Result should be 0"){
                REQUIRE(strcmp(result.c_str(), "0"));
            }
        }
    }
}


