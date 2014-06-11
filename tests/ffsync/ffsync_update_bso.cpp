#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"

std::string userIdExist("txa6eqq723apblpzum4uwtlm6vn7syl2");
std::string password("Test12345");
std::string url("http://sync.qabel.de");

using namespace std;

SCENARIO( "Encrypt a record and update the BSO on the Server"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(userIdExist,password,url, 5000);

        WHEN( "Call function updateSpecificBSO" ){
            std::string result = user->updateSpecBso("collection", FFSync::ACCOUNTS);
            time_t timestamp = time(0);

            THEN( "Result should be 1"){
                REQUIRE(result == to_string(timestamp));
            }
        }
    }
}
