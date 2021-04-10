#include <catch2/catch.hpp>

#include <mosure/api.hpp>


namespace cpp_template = mosure::cpp_template;

SCENARIO("foo scenario", "[example]") {

    GIVEN("an instance of foo") {
        cpp_template::Foo foo;

        WHEN("foo.bar() is called") {
            auto bar = foo.bar();

            THEN("the correct value is returned") {
                REQUIRE(bar == 8128);
            }
        }
    }
}
