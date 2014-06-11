#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"

std::string userId("ehoyylespiw6h4jjgbwh5vtzwzrutkgb");
std::string email("ght@gdgs.de");
std::string password("Test12345");
std::string url("http://sync.qabel.de");

using namespace std;

SCENARIO( "Create User"){

    GIVEN( "A FFSync Object") {
        FFSync *user = new FFSync(userId,password,url,5000);
        
        WHEN( "A string is pushed into the object and gets returned as hash" ){
            
            std::string result = user->createUser(email);
            

            THEN( "Result should be 1"){
                REQUIRE(result == "123434");
            }
        }
    }
}


