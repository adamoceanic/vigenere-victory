#include "catch.h"
#include "src/Lib1/Input.h"
#include "src/Lib1/matlab_api.h"


TEST_CASE("Matlab api class", "[matlab-basic]") {

    Input input;
    auto m_api = new Matlab::MatlabAPI(input);

    SECTION("actually gets default constructed") {
        REQUIRE(m_api != nullptr);
    }

    SECTION("GetCiphertextBash working correctly") {
        REQUIRE(m_api->GetCiphertextBash() == "ERROR");
    }

    SECTION("getText() working correctly") {
        REQUIRE(m_api->getText() == "ERROR");
    }

delete(m_api);
}
