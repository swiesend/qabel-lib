#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/qbl-ffsync-base32.h"

std::string user("f@f.de");
std::vector<char> cuser(user.begin(), user.end());

using namespace std;

SCENARIO( "encode a string with Base32"){

    GIVEN( "A String") {
        QblFFSyncBase32 *base = new QblFFSyncBase32;

        WHEN( "" ){
            std::string result = base->encode_Base32(cuser);

            THEN( "Result should be MZAGMLTEMU======"){
                REQUIRE(result == "MZAGMLTEMU======");
            }
        }
    }
}

SCENARIO( "decode a data with Base32 to a string"){

    GIVEN( "Data") {
        QblFFSyncBase32 *base = new QblFFSyncBase32;

        WHEN( "" ){
            std::vector<char> c = base->decode_Base32("MZAGMLTEMU======");
            std::string result = std::string(c.begin(), c.end());

            THEN( "Result should be f@f.de"){
                REQUIRE(result == "f@f.de");
            }
        }
    }
}
