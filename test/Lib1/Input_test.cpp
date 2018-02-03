#include "catch.h"
#include "src/Lib1/Input.h"


TEST_CASE("Input class basics", "[input-basic]") {
    auto input = new Input();

    SECTION("actually gets default constructed") {
        REQUIRE(input != nullptr);
    }

    SECTION("correct default constructed values") {
        REQUIRE(input->GetCiphertext().empty());
        REQUIRE(!input->HasCiphertext());
        REQUIRE(input->GetListeningStatus_Matlab());
    }

    delete(input);
}
