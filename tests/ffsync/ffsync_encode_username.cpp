#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/ffsync/ffsync.h"
#include "../../src/digest/qbl-sha1-digest.h"

SCENARIO( "1 encode a string with utf8, sha1 and Base32"){

    GIVEN( "A String f@f.de") {
        FFSync *user1 = new FFSync("f@f.de","a","b",0);

        WHEN( "string gets encoded" ){
            std::string result1 = user1->encodeUsername();

            THEN( "Result should be txa6eqq723apblpzum4uwtlm6vn7syl2"){
                REQUIRE(result1 == "txa6eqq723apblpzum4uwtlm6vn7syl2");
            }
        }
    }
}
SCENARIO( "2 encode a string with utf8, sha1 and Base32"){

    GIVEN( "A String a@f.de") {
        FFSync *user2 = new FFSync("a@f.de","a","b",0);

        WHEN( "string gets encoded" ){
            std::string result2 = user2->encodeUsername();

            THEN( "Result should be haocfmpvdehct5pocis5434msj2ecj7a"){
                REQUIRE(result2 == "haocfmpvdehct5pocis5434msj2ecj7a");
            }
        }
    }
}
SCENARIO( "3 encode a string with utf8, sha1 and Base32"){

    GIVEN( "A String ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff@f.de")
{
        FFSync *user3 = new FFSync("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff@f.de","a","b",0);

        WHEN( "string gets encoded" ){
            std::string result3 = user3->encodeUsername();

            THEN( "Result should be seavbyjqeoqketrnqiahtbzlayqknz3m"){
                REQUIRE(result3 == "seavbyjqeoqketrnqiahtbzlayqknz3m");
            }
        }
    }
}
SCENARIO( "4 encode a string with utf8, sha1 and Base32"){

    GIVEN( "A String ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff@f.de") {
        FFSync *user4 = new FFSync("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff@f.de","a","b",0);

        WHEN( "string gets encoded" ){
            std::string result4 = user4->encodeUsername();

            THEN( "Result should be 4wajtyl24rnjiarsbwvjolvkfnvwrvhz"){
                REQUIRE(result4 == "4wajtyl24rnjiarsbwvjolvkfnvwrvhz");
            }
        }
    }
}
SCENARIO( "5 encode a string with utf8, sha1 and Base32"){

    GIVEN( "A String Boumgarçon@ülülü.öl") {
        FFSync *user5 = new FFSync("Boumgarçon@ülülü.öl","a","b",0);

        WHEN( "string gets encoded" ){
            std::string result5 = user5->encodeUsername();

            THEN( "Result should be vlad4evnpsk3mgpptdaqdxauoe7kjrzo"){
                REQUIRE(result5 == "vlad4evnpsk3mgpptdaqdxauoe7kjrzo");
            }
        }
    }
}

