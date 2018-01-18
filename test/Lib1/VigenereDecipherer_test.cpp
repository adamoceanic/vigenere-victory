#include "catch.h"

#include "include/Lib1/VigenereDecipherer.h"

TEST_CASE("VigenereDecipher class basics", "[vigenere-basic]") {
    auto vig_dec = new VigenereDecipherer();

    SECTION("actually gets default constructed") {
        REQUIRE(vig_dec != nullptr);
    }

    delete(vig_dec);
}
