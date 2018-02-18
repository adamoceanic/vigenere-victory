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
        REQUIRE(input->GetListeningStatus_Matlab());
    }

    SECTION("SetHasCiphertext()") {
        input->SetHasCiphertext(true);
        REQUIRE(input->HasCiphertext());
    }

    SECTION("SetCiphertext()") {
        string ciphertext_test = "HELLOTHISISCIPHER";
        input->SetCiphertext(std::move(ciphertext_test));
        REQUIRE(input->GetCiphertext() == "HELLOTHISISCIPHER");
    }

    delete(input);
}
