#include <string>

#include "catch.h"

#include "../inc/MyClass.h"

/*
 * Memory items for using Catch
 * This is by no means exhaustive!
 */

TEST_CASE("Test that ReturnTwentyTwo does infact return 22", "[SampleTag]") {
MyClass mc;

REQUIRE(mc.ReturnTwentyTwo() == 22); // Abort test if it fails
}
/*------------------------------------------------------------*/
/*
 * Multiple assertions
 */
TEST_CASE("Test that ReturnFortyFour does infact return 44", "[SampleTag2]") {
MyClass mc;

CHECK(mc.ReturnFortyFour() == 43); // Continue rest of test if it fails
/*
 * Other assertions etc..
 */
CHECK_FALSE(mc.ReturnFalse());
REQUIRE_FALSE(mc.ReturnFalse());
}
/*------------------------------------------------------------*/
/*
 * Checking for exceptions
 */
TEST_CASE("Test that ThrowExcept does infact ", "[SampleTag3]") {

// CHECK_THROWS( /* expression */ );
// REQUIRE_THROWS( /* expression */ );

// CHECK_THROWS_AS(/* expression, type */ );
// REQUIRE_THROWS_AS (/* expression, type */ );

// during test a throw will fail the test anyway
// below just is more explicit
// CHECK_NOTHROW( /* expression */ );
// REQUIRE_NOTHROW(/* expression */ );
}
/*------------------------------------------------------------*/
/*
 * Logging
 * INFO, WARN, FAIL, CAPTURE
 */
TEST_CASE("Logging Test", "[SampleTag4]") {

INFO("MyClass mc object created");
MyClass mc;
INFO("Returned value is: " << mc.ReturnTwentyTwo());

int testVal = 10;
CAPTURE(testVal);

REQUIRE(mc.ReturnTwentyTwo() == 22); // Abort test if it fails
}
/*------------------------------------------------------------*/
/*
 * String Conversions (different from catch 1)
 * Operator <<
 * Catch::toString
 * Catch::StringMaker specialisation
 * CATCH_TRANSLATE_EXCEPTION
 */
ostream& operator<< (ostream& os, const MyType& value) {
    os << convert ( value );
    return os;
}
//or
namespace Catch
{
    std::string toString(const MyType& value) {
        return convert ( value );
    }
} // END Catch namespace
// or
// Catch StringMaker Specialisation
namespace Catch
{
    template<> struct StringMaker<T> {
        static std::string toString(const T& value) {
            return convert ( value );
        }
    };
} // END Catch namespace
// or
// Custom Exception Text
CATCH_TRANSLATE_EXCEPTION(MyType& ex) {
return ex.message();
}
/*------------------------------------------------------------*/
/*
 * Creating Test Fixtures
 */
class MyFixture {
    MyFixture() {
        // common setup code
    }
    ~MyFixture() {
        // common teardown code
    }
};

TEST_CASE_METHOD(MyFixture, "Test1") {

}
/*------------------------------------------------------------*/
/*
 * SECTIONS
 */
TEST_CASE("This is a test case") {

    // Initialisation

    SECTION("Test section 1") {
        // Test code
    }
    SECTION("Test section 2") {
        // Test code
    }
}
/*------------------------------------------------------------*/
/*
 * BDD
 */
SCENARIO("First roll is strike", "[Strike][Bowling]") {

    GIVEN("Bowled strike on first run") {
        Game game;
        game.Roll(10);

        WHEN("All the rest rolls are gutter balls") {

            RollSeveral(game, 18, 0);

            THEN("Total score is 10") {

                REQUIRE(game.Score() == 10);
            }
        }

        WHEN("Next two rolls are not spare or strike") {
            // ...
        }
    }

}