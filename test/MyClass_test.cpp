#include <string>

#include "catch/catch.h"

#include "inc/MyClass.h"

TEST_CASE("Test that ReturnTwentyTwo does infact return 22", "[SampleTag]") {
    MyClass mc;

    REQUIRE(mc.ReturnTwentyTwo() == 22); // Abort test if it fails
}

/*
 * Multiple assertions
 */
TEST_CASE("Test that ReturnFortyFour does infact return 44", "[SampleTag2]") {
    MyClass mc;

    CHECK(mc.ReturnFortyFour() == 44); // Continue rest of test if it fails
    /*
     * Other assertions etc..
     */
    CHECK_FALSE(mc.ReturnFalse());
    REQUIRE_FALSE(mc.ReturnFalse());
}
