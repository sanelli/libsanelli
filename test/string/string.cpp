#include <catch2/catch.hpp>

#include <set>
#include <iterator>

#include <sanelli/string/string.hpp>
#include <sanelli/debug/debug.hpp>

SCENARIO("Expand character class", "[sanelli][string][character_class]")
{
   std::set<char> result;

   GIVEN("The character class [a-z]")
   {
      std::string input("a-z");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = 'a'; c <= 'z'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.size() == ('z'-'a'+1));
   }

   GIVEN("The character class [0-9]")
   {
      std::string input("0-9");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = '0'; c <= '9'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.size() == 10);
   }

   GIVEN("The character class [01]")
   {
      std::string input("01");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = '0'; c <= '1'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.size() == 2);
   }

   GIVEN("The character class [a-zA-Z]")
   {
      std::string input("a-zA-Z");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = 'a'; c <= 'z'; ++c)
         REQUIRE(result.count(c) > 0);
      for (auto c = 'A'; c <= 'Z'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.size() == ('z'-'a'+1+'Z'-'A'+1));
   }

   GIVEN("The character class [a-zA-Z_]")
   {
      std::string input("a-zA-Z_");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = 'a'; c <= 'z'; ++c)
         REQUIRE(result.count(c) > 0);
      for (auto c = 'A'; c <= 'Z'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.size() == ('z'-'a'+1+'Z'-'A'+1+1));
      REQUIRE(result.count('_') > 0);
   }

   GIVEN("The character class [ab-ez]")
   {
      std::string input("ab-ez");
      sanelli::string::expand_character_class<char>(input.begin(), input.end(), std::inserter(result, result.begin()));
      
      for (auto c = 'a'; c <= 'e'; ++c)
         REQUIRE(result.count(c) > 0);
      REQUIRE(result.count('z') > 0);
      REQUIRE(result.size() == 6);
   }
}