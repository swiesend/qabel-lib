#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
#include "../../src/qbl.h"

std::string user("f@f.de");
std::string userIdExist("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string userIdDoesNotExist("z6v4uyloivun7qtfbsmu7biufkbnwp44");
std::string url("http://5.9.68.27");

SCENARIO( "start sync function"){

    GIVEN( "A String") {
        FFSync user = new FFSync();

        WHEN( "please insert string" ){
            std::string config = user->jsonToString();
            THEN( "Result should be sth like already up to date / server config is newer / client config is newer"){
                REQUIRE(false == true);
            }
        }
    }
}
