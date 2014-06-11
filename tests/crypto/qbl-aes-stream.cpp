#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../result-listener.h"
#include "../../src/crypto/qbl-aes-stream.h"
#include <openssl/aes.h>

std::string key("12345678901234561234567890123456");
std::string iv("0000000000000000");

using namespace std;

SCENARIO( "A string is encrypted and decrypted afterwards", "[QblAesStream]"){

	GIVEN( "A QblSha256Digest object" ) {
		QblAesStream a;
		a.setListener(new ResultListener());

		WHEN( "A string is pushed into the object and gets returned as hash" ){
			string testStr("TEST");
			a.init(std::vector<char>(key.begin(), key.end()),
					std::vector<char>(iv.begin(), iv.end()), QBL_CRYPTO_STREAM_ENCRYPT);
			a.pushStr(testStr);
			a.finish();

			std::string encrypted(result);

			a.init(std::vector<char>(key.begin(), key.end()),
					std::vector<char>(iv.begin(), iv.end()), QBL_CRYPTO_STREAM_DECRYPT);
			a << encrypted;
			a.finish();

			THEN( "Result is not empty" ){
				REQUIRE(result.size() != 0);
			}
			THEN( "Result should not be the encrypted string" ){
				REQUIRE(result != encrypted);
			}
			THEN( "Result should be 1 block" ){
				REQUIRE(result == testStr);
			}
		}
	}
}
SCENARIO( "A string is encrypted", "[QblAesStream]"){

	GIVEN( "A QblAesStream object" ) {
		QblAesStream a;
		a.init(std::vector<char>(key.begin(), key.end()),
				std::vector<char>(iv.begin(), iv.end()), QBL_CRYPTO_STREAM_ENCRYPT);
		a.setListener(new ResultListener());

		WHEN( "A string is pushed into the object and gets returned as hash" ){
			string testStr("TEST");
			a.pushStr(testStr);

			a.finish();

			THEN( "Result should be 1 block" ){
				REQUIRE(result.size() == AES_BLOCK_SIZE);
			}
		}
	}
}
