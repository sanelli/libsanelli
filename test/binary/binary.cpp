#include <catch2/catch.hpp>

#include <iostream>
#include <sanelli/binary/binary.hpp>

using namespace sanelli;

SCENARIO("Numeric to binary", "[binary]")
{
   const size_t size = 10;
   char output[size];
   memset(output, 0, size);
   GIVEN("A small integer value to be converted")
   {
      int i = 125;
      auto resut_size = binary_converter::to_binary(i, output);
      REQUIRE(output[0] == (char)125);
      REQUIRE(output[1] == (char)0);
      REQUIRE(output[2] == (char)0);
      REQUIRE(output[3] == (char)0);
   }

   GIVEN("A big integer value to be converted")
   {
      int i = 125007;
      auto resut_size = binary_converter::to_binary(i, output);
      REQUIRE(output[0] == (char)79);
      REQUIRE(output[1] == (char)-24);
      REQUIRE(output[2] == (char)1);
      REQUIRE(output[3] == (char)0);
   }
}

SCENARIO("Binary to numeric", "[binary]")
{
   const size_t size = 10;
   char intput[size];
   memset(intput, 0, size);
   GIVEN("A small integer value to be converted from")
   {
      intput[0] = 125;
      auto result = binary_converter::from_binary<int>(intput);
      REQUIRE(result == 125);
   }

   GIVEN("A big integer value to be converted from")
   {
      intput[0] = 79;
      intput[1] = -24;
      intput[2] = 1;
      auto result = binary_converter::from_binary<int>(intput);
      REQUIRE(result == 125007);
   }
}
