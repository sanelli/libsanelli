#include <catch2/catch.hpp>
#include <sanelli/sanelli.hpp>

using namespace sanelli;

SCENARIO("Sign management", "[math][sign]")
{

   GIVEN("Some values")
   {

      WHEN("The values are (signed) integer")
      {
         REQUIRE(sign(+100) == +1);
         REQUIRE(sign(0) == 0);
         REQUIRE(sign(-100) == -1);
      }

      WHEN("The values are (unsigned) integer")
      {
         REQUIRE(sign(+100u) == +1);
         REQUIRE(sign(0u) == 0);
      }

      WHEN("The values are float")
      {
         REQUIRE(sign(+100.00f) == +1);
         REQUIRE(sign(0.00f) == 0);
         REQUIRE(sign(-100.00f) == -1);
      }

      WHEN("The values are double")
      {
         REQUIRE(sign(+100.00) == +1);
         REQUIRE(sign(0.00) == 0);
         REQUIRE(sign(-100.00) == -1);
      }

      WHEN("The values are char")
      {
         REQUIRE(sign((char)+100) == +1);
         REQUIRE(sign((char)0) == 0);
         REQUIRE(sign((char)-100) == -1);
      }

      WHEN("The values are boolean")
      {
         REQUIRE(sign(true) == +1);
         REQUIRE(sign(false) == 0);
      }
   }
}
