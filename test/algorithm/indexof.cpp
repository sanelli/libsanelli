#include <catch2/catch.hpp>
#include <vector>
#include <sanelli/algorithm/algorithm.hpp>

SCENARIO("Index algorithm", "[algorithm]")
{
   GIVEN("a vector")
   {
      std::vector<int> v = { 1,2,3,4,5,6 };
      WHEN("Looking for an existing item")
      {
         auto index = sanelli::indexof(v.begin(), v.end(), 3);
         REQUIRE(index == 4);
      } 

      WHEN("Looking for an existing item by function")
      {
         auto index = sanelli::indexof_if(v.begin(), v.end(), [](int value){ return value == 3; });
         REQUIRE(index == 4);
      } 

      WHEN("Looking for a non-existing item")
      {
         auto index = sanelli::indexof(v.begin(), v.end(), 77);
         REQUIRE(index == -1);
      } 

      WHEN("Looking for a non-existing item by function")
      {
         auto index = sanelli::indexof_if(v.begin(), v.end(), [](int value) { return value == 77; });
         REQUIRE(index == -1);
      } 
   }
}