#include <catch2/catch.hpp>

#include <memory>
#include <sstream>

#include <sanelli/tree/tree.hpp>

SCENARIO("Visiting a tree", "[tree],[visit]")
{
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

      WHEN("the tree is visited")
      {
         std::stringstream stream;
         auto callback = [&stream](std::shared_ptr<sanelli::tree::node<char>> node_tree) -> void {
            if (node_tree->has_value())
               stream << node_tree->get();
         };
         sanelli::tree::visit_preorder(root, callback);
         auto result = stream.str();
         REQUIRE(result == "efbcghia");
      }
   }
}