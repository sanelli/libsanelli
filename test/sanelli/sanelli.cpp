#include <catch2/catch.hpp>

#include <sanelli/sanelli.hpp>

SCENARIO("Test generic common high level function", "[sanelli][common]")
{
   GIVEN("Get the current version")
   {
      REQUIRE(sanelli::get_version() == "1.0");
   }
}