#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/fs/qbl-fs.h"

SCENARIO( "Empty directory.", "[QblFs]") {
    GIVEN( "A QblFs object." ) {
        QblFs a;
        a.setRootPath("fs/empty_dir");
        
        WHEN( "A empty directory is scanned and compared" ) {
            std::unordered_set<std::string> result = a.compare();
            THEN( "The returned list contains only the directory" ) {
                REQUIRE(result.size() == 1);
                auto it = result.begin();
                REQUIRE(*it == "fs/empty_dir");
            }
        }
    }
}

SCENARIO ("Directory with files and no changes.", "[QblFs]") {
    GIVEN( "A QblFs object and a map to write to." ) {
        QblFs a;
        a.setRootPath("fs/nochange_dir");
        std::unordered_set<std::string> result;

        WHEN( "A directory is scanned and compared" ) {
            result = a.compare();
            THEN( "The returned list contains all files in the dir and the directory." ) {
                REQUIRE(result.size() == 3);
            }
        }
        WHEN( "A directory is scanned and compared twice" ) {
            THEN( "The returned list should be empty" ){
                std::unordered_set<std::string> result2 = a.compare();
                REQUIRE(result == result2);
            }
        }
    }
}


