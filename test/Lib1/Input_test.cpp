#include "catch.h"
#include "include/Lib1/Input.h"


TEST_CASE("Input class basics", "[input-basic]") {
    auto input = new Input();

    SECTION("actually gets default constructed") {
        REQUIRE(input != nullptr);
    }

    delete(input);
}
