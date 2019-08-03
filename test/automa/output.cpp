#include <catch2/catch.hpp>

#include <memory>
#include <sstream>

#include <sanelli/automa/automa.hpp>

SCENARIO("Automaton output is required")
{

   GIVEN("few simple automatons")
   {
      std::string letters1("abc");
      auto atm1 = sanelli::create_selection_automaton<char, unsigned int>(letters1.begin(), letters1.end());

      std::string letters2("def");
      auto atm2 = sanelli::create_selection_automaton<char, unsigned int>(letters2.begin(), letters2.end());

      WHEN("they are joined together (&)")
      {

         auto result = atm1 & atm2;
         REQUIRE(result != nullptr);

         auto output = sanelli::to_graphziv(result);
         REQUIRE(output == "digraph { \n"
         "rankdir = LR \n"
         "node [ label = \"1\", shape = diamond]; 1;\n"
         "node [ label = \"2\", shape = circle]; 2;\n"
         "node [ label = \"3\", shape = doublecircle]; 3;\n"
         "1 -> 2 [label = \"a\"]\n"
         "1 -> 2 [label = \"b\"]\n"
         "1 -> 2 [label = \"c\"]\n"
         "2 -> 3 [label = \"d\"]\n"
         "2 -> 3 [label = \"e\"]\n"
         "2 -> 3 [label = \"f\"]\n"
         "}\n");
      }
   }
}