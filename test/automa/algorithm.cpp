#include <catch2/catch.hpp>

#include <memory>
#include <sstream>

// #include <iostream>

#include <sanelli/automa/automa.hpp>

SCENARIO("Automaton creation with algorithms")
{
   GIVEN("a sequence of values")
   {
      std::string letters("abcdef");
      WHEN("An automaton with a single edge is created")
      {
         auto atm = sanelli::automa::create_single_value<char>(letters[0]);
         REQUIRE(atm != nullptr);
         REQUIRE(atm->get_number_of_states() == 2);
         REQUIRE(atm->has_state(1));
         REQUIRE(atm->has_state(2));
         REQUIRE(atm->has_edge(1, letters[0], 2));
         REQUIRE(atm->get_initial_state() == 1);
         REQUIRE_FALSE(atm->is_final_state(1));
         REQUIRE(atm->is_final_state(2));
      }

      WHEN("An automaton with a multiple edge is created")
      {
         auto atm = sanelli::automa::create_selection_automaton<char, unsigned int>(letters.begin(), letters.end());
         REQUIRE(atm != nullptr);
         REQUIRE(atm->get_number_of_states() == 2);
         REQUIRE(atm->has_state(1));
         REQUIRE(atm->has_state(2));
         REQUIRE(atm->has_edge(1, letters[0], 2));
         REQUIRE(atm->has_edge(1, letters[1], 2));
         REQUIRE(atm->has_edge(1, letters[2], 2));
         REQUIRE(atm->has_edge(1, letters[3], 2));
         REQUIRE(atm->has_edge(1, letters[4], 2));
         REQUIRE(atm->has_edge(1, letters[5], 2));
         REQUIRE(atm->get_initial_state() == 1);
         REQUIRE_FALSE(atm->is_final_state(1));
         REQUIRE(atm->is_final_state(2));
      }
   }

   GIVEN("two simple automaton"){
      
      std::string letters1("abc");
      auto atm1 = sanelli::automa::create_selection_automaton<char, unsigned int>(letters1.begin(), letters1.end());

      std::string letters2("def");
      auto atm2 = sanelli::automa::create_selection_automaton<char, unsigned int>(letters2.begin(), letters2.end());

      std::string letters3("ghi");
      auto atm3 = sanelli::automa::create_selection_automaton<char, unsigned int>(letters3.begin(), letters3.end());

      WHEN("they are joined together (&)"){

         auto result = atm1 & atm2;
         REQUIRE(result != nullptr);
         REQUIRE(result->get_number_of_states() == 3);
         REQUIRE(result->has_state(1));
         REQUIRE(result->has_state(2));
         REQUIRE(result->has_state(3));
         REQUIRE(result->has_edge(1, letters1[0], 2));
         REQUIRE(result->has_edge(1, letters1[1], 2));
         REQUIRE(result->has_edge(1, letters1[2], 2));
         REQUIRE(result->has_edge(2, letters2[0], 3));
         REQUIRE(result->has_edge(2, letters2[1], 3));
         REQUIRE(result->has_edge(2, letters2[2], 3));
         REQUIRE(result->get_initial_state() == 1);
         REQUIRE_FALSE(result->is_final_state(1));
         REQUIRE_FALSE(result->is_final_state(2));
         REQUIRE(result->is_final_state(3));
      }

       WHEN("they are disjoined together (|)"){

         auto result = atm1 | atm2;
         REQUIRE(result != nullptr);

         //std::cout << sanelli::automa::to_graphziv(result) << std::endl;
      }

      WHEN("they are disjoined together (|)"){

         auto result = atm1 | atm2 | atm3;
         REQUIRE(result != nullptr);

         //std::cout << sanelli::automa::to_graphziv(result) << std::endl;
      }
   }
}