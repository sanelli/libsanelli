#include <catch2/catch.hpp>

#include <sanelli/memory/memory.hpp>

SCENARIO("Share pointer generation", "[memory]"){
   
    GIVEN("A type"){

       WHEN("A shared pointer is generated") {
         auto result =  sanelli::memory::make_shared<unsigned int>();
         REQUIRE(result != nullptr);
       }
    }
}
