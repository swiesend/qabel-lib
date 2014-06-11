#define CATCH_CONFIG_MAIN
#include <cstring>
#include <vector>
#include "../catch.hpp"
#include "../result-listener.h"
#include "../../src/digest/qbl-sha256-digest.h"

SCENARIO( "A hash is generated", "[QblSha256Digest]"){

	GIVEN( "A QblSha256Digest object" ) {
		QblSha256Digest a;
		a.init();
		a.setListener(new ResultListener);

		WHEN( "A string is pushed into the object and gets returned as hash" ){
			a.pushStr(std::string("TEST"));
			a.finish();

			THEN( "The string has the size 256/8" ){
				REQUIRE(result.size() != 0);
				REQUIRE(result.size() == 256/8);
			}
			THEN( "The hash is calculated correctly" ){
				char hash_string[EVP_MAX_MD_SIZE*2+1];
				for(unsigned int i = 0; i < result.size(); i++) {
					snprintf(hash_string + i*2, 3, "%02x", result[i] & 0xFF);
				}
				REQUIRE(std::string(hash_string) == "94ee059335e587e501cc4bf90613e0814f00a7b08bc7c648fd865a2af6a22cc2");
			}
		}
	}
}

SCENARIO( "Different hashes are generated", "[QblSha256Digest]"){

	GIVEN( "Two QblSha256Digest objects" ) {
		QblSha256Digest a;
		QblSha256Digest b;
		a.setListener(new ResultListener);
		a.init();
		b.setListener(new ResultListener);
		b.init();

		WHEN( "Two strings are pushed into the object and get hashed" ) {
			a.pushStr("TEST");
			b.pushStr("NOTEST");
			a.finish();
			std::string hashB(result);
			b.finish();

			THEN( "The hashes are different"){
				REQUIRE( result != hashB );
			}
		}
	}
}
