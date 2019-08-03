#include <catch2/catch.hpp>

#include <sanelli/tree/tree.hpp>

SCENARIO("Creating a tree", "[tree],[create]")
{
   GIVEN("Adding a single node WITHOUT a value")
   {
      auto node = sanelli::node<char>::make();
      REQUIRE(node != nullptr);
      REQUIRE(node->is_leaf());
      REQUIRE_FALSE(node->has_value());
      REQUIRE_THROWS_AS(node->get(), sanelli::tree_error);
      REQUIRE(node->get_children_count() == 0);

      WHEN("A value is set")
      {
         node->set('w');
         REQUIRE(node->get() == 'w');
      }

      WHEN("A node is added by value")
      {
         node->add_child('q');
         REQUIRE(node->get_children_count() == 1);
         REQUIRE_FALSE(node->is_leaf());
         auto child = node->child_at(0);
         REQUIRE(child != nullptr);
         REQUIRE(child->is_leaf());
         REQUIRE(child->get_children_count() == 0);

         REQUIRE_THROWS_AS(node->child_at(1), sanelli::tree_error);
      }
   }

   GIVEN("Adding a single node WITH a value")
   {
      auto node = sanelli::node<char>::make('x');
      REQUIRE(node != nullptr);
      REQUIRE(node->is_leaf());
      REQUIRE(node->get() == 'x');
      REQUIRE(node->has_value());
      REQUIRE(node->get_children_count() == 0);
   }

   GIVEN("A node with multiple children")
   {
      std::vector<char> values = {'a',
                                  'b',
                                  'c'};
      auto node = sanelli::node<char>::make();
      for (auto vit = values.begin(); vit != values.end(); ++vit)
      {
         node->add_child(*vit);
      }

      REQUIRE(node->get_children_count() == 3);

      WHEN("user iterate over them")
      {
         int index = 0;
         for (auto it = node->begin(); it != node->end(); ++it, ++index)
         {
            auto child = *it;
            REQUIRE(child->get() == values.at(index));
            REQUIRE(node->child_at(index)->get() == values.at(index));
         }
         REQUIRE(index == 3);
      }

      WHEN("user iterate over them (CONST)")
      {
         int index = 0;
         for (auto it = node->cbegin(); it != node->cend(); ++it, ++index)
         {
            auto child = *it;
            REQUIRE(child->get() == values.at(index));
            REQUIRE(node->child_at(index)->get() == values.at(index));
         }
         REQUIRE(index == 3);
      }
   }
}