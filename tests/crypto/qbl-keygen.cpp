#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/crypto/qbl-keygen.cpp"

using namespace std;

SCENARIO( "Randombytes are created for AES", "[QblKeygen]"){
	GIVEN( "A functioncall to aes keygen" ) {
		vector<char> result = qblKeyGenAes256();
		THEN( "Result should be 256 bit" ){
			REQUIRE(result.size() == 32);
		}

		THEN( "Result not give the same result again" ){
			REQUIRE(result != qblKeyGenAes256());
		}
	}
}
