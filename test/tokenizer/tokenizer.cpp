#include <catch2/catch.hpp>
#include <string>
#include <vector>

#include <sanelli/tokenizer/tokenizer.hpp>

SCENARIO("Tokenizer", "[tokenizer]"){

   sanelli::tokenizer<unsigned int> tokenizer;
   
    GIVEN("A set of rules"){

       tokenizer.add(1, "a", true, true);
       tokenizer.add(2, "b", true, true);
       tokenizer.add(3, "c", true, true);

       WHEN("Parsing rules") {
         std::string input("a b a a c c");
         std::vector<sanelli::token<unsigned int>> output;

         tokenizer.tokenize(input, 0, output);
         REQUIRE(output.size() == 6);
       }
    }
}