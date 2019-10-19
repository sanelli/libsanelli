#include <catch2/catch.hpp>

#include <sanelli/io/io.hpp>

using namespace sanelli;

SCENARIO("Console colour", "[io]"){
    GIVEN("The colour set"){
      REQUIRE(console_colour::reset() != nullptr);
      REQUIRE(console_colour::black() != nullptr);
      REQUIRE(console_colour::red() != nullptr);
      REQUIRE(console_colour::green() != nullptr);
      REQUIRE(console_colour::yellow() != nullptr);
      REQUIRE(console_colour::blue() != nullptr);
      REQUIRE(console_colour::magenta() != nullptr);
      REQUIRE(console_colour::cyan() != nullptr);
      REQUIRE(console_colour::white() != nullptr);
      REQUIRE(console_colour::bold_black() != nullptr);
      REQUIRE(console_colour::bold_red() != nullptr);
      REQUIRE(console_colour::bold_green() != nullptr);
      REQUIRE(console_colour::bold_yellow() != nullptr);
      REQUIRE(console_colour::bold_blue() != nullptr);
      REQUIRE(console_colour::bold_magenta() != nullptr);
      REQUIRE(console_colour::bold_cyan() != nullptr);
      REQUIRE(console_colour::bold_white() != nullptr);      
    }
}
