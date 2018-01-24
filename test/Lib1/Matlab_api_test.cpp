#include "catch.h"
#include "src/Lib1/matlab_api.h"


TEST_CASE("Matlab api class", "[matlab-basic]") {
    auto m_api = new MatlabAPI();

    SECTION("actually gets default constructed") {
        REQUIRE(m_api != nullptr);
    }

    SECTION("GetCiphertextBash working correctly") {
        REQUIRE(m_api->GetCiphertextBash() == "ERROR");
    }

delete(m_api);
}
