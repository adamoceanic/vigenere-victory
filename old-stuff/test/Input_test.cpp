#include "catch/catch.h"

#include "../Lib1/inc/Input.h"

TEST_CASE("Input class basics", "[vigenere-basic]") {
    auto input = new Input();

    SECTION("actually gets default constructed") {
        REQUIRE(input != nullptr);
    }

    delete(input);
}