#include <catch2/catch.hpp>

#include <sanelli/tree/tree.hpp>

SCENARIO("Outputting a tree")
{
   GIVEN("A tree with two levels")
   {
      auto root = sanelli::tree::node<char>::make('a');
      root->add_child('b');
      root->add_child('c');
      root->add_child('d');

      WHEN("the graphviz description is generated")
      {
         auto graphviz = sanelli::tree::to_graphviz(root);
         REQUIRE(graphviz.size() > 0);
      }
   }

    GIVEN("A tree with three levels")
   {
      auto root = sanelli::tree::node<char>::make('a');
      auto child_b = root->add_child('b');
      auto child_c = root->add_child('c');
      auto child_d = sanelli::tree::node<char>::make();
      root->add_child(child_d);

      auto child_e = child_b->add_child('e');
      auto child_f = child_b->add_child('f');
      auto child_g = child_d->add_child('g');
      auto child_h = child_d->add_child('h');
      auto child_i = child_d->add_child('i');

      WHEN("the graphviz description is generated")
      {
         auto graphviz = sanelli::tree::to_graphviz(root);
         REQUIRE(graphviz.size() > 0);
      }
   }
}