#include "catch.h"
#include "include/Lib1/Input.h"
#include "src/Lib1/Input_Impl.h"


TEST_CASE("Input class basics", "[vigenere-basic]") {
    auto input = new Input();

    SECTION("actually gets default constructed") {
        REQUIRE(input != nullptr);
    }

    delete(input);
}

TEST_CASE("Input_Impl class basics", "[vigenere-basic]") {
    auto input = new Input_Impl();

    SECTION("actually gets default constructed") {
        REQUIRE(input != nullptr);
    }

    delete(input);
}