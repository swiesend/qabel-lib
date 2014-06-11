#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
#include "../../src/crypto/qbl-keygen.h"

std::string toBeEncrypted("1234567890123456");
std::vector<char> key = qblKeyGenAes256();
std::vector<char> iv = qblKeyGenAes256IV();

SCENARIO( "encode a string with aes256cbc"){

    GIVEN( "The String 1234567890123456") {
        FFSync ffsync("sasdf", "sadfsd", "sadfsd", 2);

        WHEN( "String is encrypted" ){
            std::string encryptedInput = ffsync.encrypt(toBeEncrypted, iv);
            std::string decryptedInput = ffsync.decrypt(encryptedInput, iv);
            THEN( "Result should be test"){
                REQUIRE(decryptedInput == "1234567890123456");
            }
        }
    }
}
