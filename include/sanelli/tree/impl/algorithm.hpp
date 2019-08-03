#pragma once

#include <memory>
#include <functional>

#include <sanelli/tree/impl/node.hpp>

namespace sanelli
{

template <typename TValue,
          typename TCallback>
void visit_preorder(std::shared_ptr<node<TValue>> tree,
                    TCallback node_callback)
{
   for (auto it = tree->cbegin(); it != tree->cend(); ++it)
   {
      auto child = *it;
      visit_preorder(child, node_callback);
   }
   node_callback(tree);
}

} // namespace sanelli