#include <catch2/catch.hpp>

#include <sanelli/fuzzy/fuzzy.hpp>

using namespace sanelli;

SCENARIO("Fuzzy logic", "[fuzzy]"){
   
    GIVEN("Two fuzzy variables"){

       fuzzy_variable<float> foo(0.6f);
       fuzzy_variable<float> bar(0.4f);

       WHEN("Getting constant truth values zero and one"){
         auto fuzzy_zero = zero<float>();
         auto fuzzy_one = one<float>();
         REQUIRE((fuzzy_zero && foo) == fuzzy_zero);
         REQUIRE((fuzzy_zero || foo) == foo);
         REQUIRE((fuzzy_one && foo) == foo);
         REQUIRE((fuzzy_one || foo) == fuzzy_one);
       }

       WHEN("Creating a third variable"){
          auto other = make_fuzzy(100.0f);
          REQUIRE(other.value() != 100);
          REQUIRE(other.value() <= 1);
          REQUIRE(other.value() >= 0);
       }

       WHEN("Using copy constructor and assignment") {
          fuzzy_variable<float> other(foo);
          REQUIRE(other == foo);
          other = bar;
         REQUIRE(other == bar);
       }

       WHEN("Operators are applies") {
          auto and_result = foo && bar;
          REQUIRE(and_result.value() == 0.4f);
          auto or_result = foo || bar;
          REQUIRE(or_result.value() == 0.6f);
          auto not_result = !bar;
          REQUIRE(not_result.value() == 0.6f);
       }
    }
}
