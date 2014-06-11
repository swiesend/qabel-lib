#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "result-listener.h"
#include "../src/qbl-pipe.h"

class PipeTest : public QblPipe {
public:
    virtual ~PipeTest() {

    }

    virtual void push(const std::vector<char> &data){
        getListener()->onData(data);
    }

    virtual void finish(){
        getListener()->onFinish();
    }
};

SCENARIO( "Quick generator is used", "[QblPipe]"){

    GIVEN( "A QblPipe object" ) {
        PipeTest a;

        WHEN( "A string is pushed into the object and gets returned" ){
            std::string* hash = a.create("TEST");


            THEN( "The string gets returned" ){
                REQUIRE(*hash == "TEST");
            }
        }
    }
}

SCENARIO( "<<-Operator is used", "[QblPipe]"){

    GIVEN( "A QblPipe object" ) {
        PipeTest a;
        char testStr[] = "TEST";
        a.setListener(new ResultListener());
        a << testStr;

        WHEN( "A string is pushed into the object and gets returned" ){
            THEN( "The string gets returned" ){
                REQUIRE(result == testStr);
            }
        }
    }
}
