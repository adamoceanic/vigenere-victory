#include "catch.h"
#include "src/Lib1/Input.h"
#include "src/Lib1/matlab_api.h"


TEST_CASE("Matlab api class", "[matlab-basic]") {

    Input input;
    auto m_api = new MatlabAPI(input);

    SECTION("actually gets default constructed") {
        REQUIRE(m_api != nullptr);
    }

    SECTION("GetCiphertextBash working correctly") {
        REQUIRE(m_api->GetCiphertextBash() == "ERROR");
    }

    SECTION("GetCiphertextTxt working correctly") {
        REQUIRE(m_api->GetCiphertextTxt() == "ERROR");
    }

delete(m_api);
}
