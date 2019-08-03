#pragma once

#include <string>
#include <memory>
#include <sstream>

#include <sanelli/tree/impl/node.hpp>

namespace sanelli
{
namespace impl
{
template <typename TValue>
void to_graphviz(std::shared_ptr<node<TValue>> node,
                 std::stringstream &stream_nodes,
                 std::stringstream &stream_arrows,
                 unsigned int parent_node,
                 unsigned int& node_counter)
{

   if(parent_node == 0){
      auto shape = node->has_value() ? "circle" : "point";
      stream_nodes << "node [ shape = " << shape << ", label= \"";
      if(node->has_value()) stream_nodes << node->get();
      stream_nodes << "\" ]; " << parent_node << ";" << std::endl;
   }

   for (auto it = node->cbegin(); it != node->cend(); ++it)
   {
      auto child = *it;

      ++node_counter;
      auto shape = child->has_value() ? "circle" : "point";
      stream_nodes << "node [ shape = " << shape << ", label= \"";
      if(child->has_value()) stream_nodes << child->get();
      stream_nodes << "\" ]; " << node_counter << ";" << std::endl;
      stream_arrows << parent_node << " -- " << node_counter << std::endl;
      to_graphviz(child, stream_nodes, stream_arrows, node_counter, node_counter);
   }
}

} // namespace impl

template <typename TValue>
std::string to_graphviz(std::shared_ptr<node<TValue>> node)
{
   unsigned int node_counter = 0;
   std::stringstream stream_nodes, stream_arrow;
   impl::to_graphviz(node, stream_nodes, stream_arrow, node_counter, node_counter);

   return std::string("graph {\n") 
   + stream_nodes.str()
   + stream_arrow.str()
   + " }\n";
}

} // namespace sanelli