#include <catch2/catch.hpp>
#include <string>

#include <sanelli/string/string.hpp>

SCENARIO("String generation", "[string]")
{

   GIVEN("A set of variables")
   {

      auto a = "Hello world";
      auto b = 33;
      auto c = std::string("XXX");

      WHEN("A string is created")
      {
         auto result = sanelli::make_string(a, b, c);
         REQUIRE(result == "Hello world33XXX");
      }
   }
}

SCENARIO("String trimming", "[string]")
{

   GIVEN("A set of strings")
   {

      std::string a{"hello world"};
      std::string b{"  hello world"};
      std::string c{"hello world  "};
      std::string d{"  hello world  "};

      WHEN("Left trimming")
      {
         sanelli::ltrim(a);
         REQUIRE(a == "hello world");
         sanelli::ltrim(b);
         REQUIRE(b == "hello world");
         sanelli::ltrim(c);
         REQUIRE(c == "hello world  ");
         sanelli::ltrim(d);
         REQUIRE(d == "hello world  ");
      }

      WHEN("Right trimming")
      {
         sanelli::rtrim(a);
         REQUIRE(a == "hello world");
         sanelli::rtrim(b);
         REQUIRE(b == "  hello world");
         sanelli::rtrim(c);
         REQUIRE(c == "hello world");
         sanelli::rtrim(d);
         REQUIRE(d == "  hello world");
      }
   }
}

SCENARIO("String splitting", "[string]")
{
   GIVEN("A string")
   {
      std::string str("Hello world/ this is me/ Life should be/ fun for everyone");
      std::vector<std::string> v;
      WHEN("A string is splitted by space")
      {
         sanelli::split(str, ' ', v);
         REQUIRE(v.size() == 11);
      }

      WHEN("A string is splitted by '/'")
      {
         sanelli::split(str, '/', v);
         REQUIRE(v.size() == 4);
      }
   }
}