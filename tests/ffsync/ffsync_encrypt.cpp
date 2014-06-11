#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
std::string toBeEncrypted("1234567890123456");

SCENARIO( "encode a string with aes256cbc"){

    GIVEN( "A String -test-") {
        FFSync ffsync("sasdf", "sadfsd", "sadfsd", 2);
        WHEN( "String is encrypted" ){
            std::string encryptedInput = ffsync.encrypt(toBeEncrypted);
            THEN( "Result should be U2FsdGVkX19kazTJaQmegK6xsJCJ/BSHzZikblw5ut0="){
                REQUIRE(encryptedInput != ffsync.encrypt(toBeEncrypted));
            }
        }
    }
}
