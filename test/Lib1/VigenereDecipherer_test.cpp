#include "catch.h"

#include "src/Lib1/VigenereDecipherer.h"

TEST_CASE("VigenereDecipher class basics", "[vigenere-decipherer]") {
    auto vig_dec = new VigenereDecipherer();

    SECTION("actually gets default constructed") {
        REQUIRE(vig_dec != nullptr);
    }

    delete(vig_dec);
    
}

TEST_CASE("removeNgramsBelowOccurrenceThreshold", "[vigenere-decipherer]") {
    
}

TEST_CASE("getAllNgramsWithLength", "[vigenere-decipherer]") {

}

TEST_CASE("searchForRecurringNgramsWithLength", "[vigenere-decipherer]") {

}