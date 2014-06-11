#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
#include <iostream>

std::string userId("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test123456");
std::string url("http://praecloud.prae.local");
std::string deleteUser("q7pzw45ksdydnxjauk5ewo4fpife5pp6");
std::string deletePassword("Test12345");
int port = 5000;
std::string path("addons");

using namespace std;

SCENARIO( "Delete user storage"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(deleteUser, deletePassword, url, port);

        WHEN( "A delete request is send to the ffsync server" ){
            std::string result = user->deleteUserstorage();
            std::string test = result;
            THEN( "Result should be 1"){
                REQUIRE("2" == "1");
            }
        }
    }
}
