#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"

std::string userIdExist("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string url("http://sync.qabel.de");

SCENARIO( "Encrypt a record and update the BSO on the Server"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync();
        

        WHEN( "Call functioninitNewServer" ){
            
            user->initNewServer("collection");
            
            THEN( "Result should be 1"){
                REQUIRE(2 == 3);
            }
        }
    }
}

