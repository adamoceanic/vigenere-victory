#include "catch.h"

#include "include/Lib1/Vigenere.h"

TEST_CASE("Vigenere class basics", "[vigenere-basic]") {
    auto vig = new Vigenere();

    SECTION("actually gets default constructed") {
        REQUIRE(vig != nullptr);
    }


    delete(vig);
}
