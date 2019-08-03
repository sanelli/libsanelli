#include <catch2/catch.hpp>

#include <memory>
#include <set>
#include <iterator>

#include <sanelli/automa/automa.hpp>
#include <sanelli/debug/debug.hpp>

SCENARIO("Automaton creation with algorithms")
{
   GIVEN("a sequence of values")
   {
      std::string letters("abcdef");
      WHEN("An automaton with a single edge is created")
      {
         auto atm = sanelli::create_single_value<char>(letters[0]);
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
         auto atm = sanelli::create_selection_automaton<char, unsigned int>(letters.begin(), letters.end());
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

   GIVEN("three simple automaton")
   {
      std::string letters1("abc");
      auto atm1 = sanelli::create_selection_automaton<char, unsigned int>(letters1.begin(), letters1.end());

      std::string letters2("def");
      auto atm2 = sanelli::create_selection_automaton<char, unsigned int>(letters2.begin(), letters2.end());

      std::string letters3("ghi");
      auto atm3 = sanelli::create_selection_automaton<char, unsigned int>(letters3.begin(), letters3.end());

      WHEN("two of them are joined together (&)")
      {
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

      WHEN("thwo of them are disjoined together (|)")
      {
         auto result = atm1 | atm2;
         REQUIRE(result != nullptr);
      }

      WHEN("three of them are disjoined together (|)")
      {

         auto result = atm1 | atm2 | atm3;
         REQUIRE(result != nullptr);
      }

      WHEN("the * operator is applied to one of them")
      {
         auto result = sanelli::operator*(atm1);
         REQUIRE(result != nullptr);
      }

      WHEN("the + operator is applied to one of them")
      {
         auto result = +atm1;
         REQUIRE(result != nullptr);
      }
   }
}

SCENARIO("Automaton execution", "[automa][algo][match]")
{
   GIVEN("A simple automaton in the form ((a|b)c)+")
   {
      auto atm1 = sanelli::create_single_value<char, unsigned int>('a');
      auto atm2 = sanelli::create_single_value<char, unsigned int>('b');
      auto atm3 = sanelli::create_single_value<char, unsigned int>('c');

      auto atm = +((atm1 | atm2) & atm3);

      WHEN("matches string 'ac'")
      {
         std::string str("ac");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(atm->is_final_state(result.first));
         REQUIRE(result.second == str.end());
      }

      WHEN("matches string 'acac'")
      {
         std::string str("acac");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(atm->is_final_state(result.first));
         REQUIRE(result.second == str.end());
      }

      WHEN("matches string 'bcac'")
      {
         std::string str("bcac");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(atm->is_final_state(result.first));
         REQUIRE(result.second == str.end());
      }

      WHEN("does not match string 'aca'")
      {
         std::string str("aca");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(result.first == atm->zero_state());
         REQUIRE(result.second == str.end());
      }

      WHEN("does not match string 'xxx'")
      {
         std::string str("xxx");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(result.first == atm->zero_state());
      }
   }

   GIVEN("A simple automaton in the form ((a|b)c)")
   {
      auto atm1 = sanelli::create_single_value<char, unsigned int>('a');
      auto atm2 = sanelli::create_single_value<char, unsigned int>('b');
      auto atm3 = sanelli::create_single_value<char, unsigned int>('c');

      auto atm = (atm1 | atm2) & atm3;

      WHEN("matches string 'ac'")
      {
         std::string str("ac");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(atm->is_final_state(result.first));
         REQUIRE(result.second == str.end());
      }

      WHEN("matches string 'bc'")
      {
         std::string str("bc");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(atm->is_final_state(result.first));
         REQUIRE(result.second == str.end());
      }

      WHEN("does not match string 'aca'")
      {
         std::string str("aca");
         auto result = sanelli::run_automaton(atm, str.begin(), str.end());
         REQUIRE(result.first == atm->zero_state());
      }
   }
}