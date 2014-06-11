#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"

std::string user("f@f.de");
std::string userIdExist("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string userIdDoesNotExist("z6v4uyloivun7qtfbsmu7biufkbnwp44");
std::string url("http://sync.qabel.de");


SCENARIO( "start sync function"){

    GIVEN( "A FFSync Object") {
        FFSync *ffsync = new FFSync();

        WHEN( "Sync function is called" ){
            bool result = ffsync->sync();
            THEN( "Server Timestamp and local Timestamp should be equal"){

                REQUIRE(result == true);
            }
        }
    }
}
