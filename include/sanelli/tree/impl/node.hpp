#pragma once

#include <vector>
#include <memory>
#include <utility>

#include <sanelli/tree/impl/exception.hpp>

namespace sanelli::tree
{
template <typename TValue>
class node
{
 private:
   std::vector<std::shared_ptr<node<TValue>>> _children;
   TValue value;

   node() {}
   node(TValue value)
   {
      this->value = value;
   }

 public:
   // Makers
   static std::shared_ptr<node<TValue>> make(TValue value)
   {
      return std::shared_ptr<node<TValue>>(new node(value));
   }

   static std::shared_ptr<node<TValue>> make()
   {
      return std::shared_ptr<node<TValue>>(new node<TValue>());
   }

   // Member types
   using const_iterator = typename std::vector<std::shared_ptr<node<TValue>>>::const_iterator;
   using iterator = typename std::vector<std::shared_ptr<node<TValue>>>::iterator;
   using size_type = typename std::vector<std::shared_ptr<node<TValue>>>::size_type;

   // Value management
   TValue get() const noexcept { return value; }
   void set(TValue value) { this->value = value; }

   // Children management
   void add_child(TValue value)
   {
      add_child(make(value));
   }

   void add_child(std::shared_ptr<node<TValue>> node)
   {
      _children.push_back(node);
   }

   std::shared_ptr<node<TValue>> child_at(size_type index) const
   {
      try
      {
         return _children.at(index);
      }
      catch (std::out_of_range e)
      {
         std::string message("No such child at index ");
         message += std::to_string(index);
         throw tree_error(message);
      }
   }

   // Enumerate children
   auto begin() const noexcept { return _children.begin(); }
   auto end() const noexcept { return _children.end(); }
   auto cbegin() const noexcept { return _children.cbegin(); }
   auto cend() const noexcept { return _children.cend(); }

   // properties
   size_type get_children_count() const noexcept { return _children.size(); }
   bool is_leaf() const noexcept { return _children.size() == 0; }
};
} // namespace sanelli::tree