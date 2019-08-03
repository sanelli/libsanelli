#pragma once

#include <vector>
#include <memory>
#include <utility>

#include <sanelli/tree/impl/exception.hpp>

namespace sanelli
{
template <typename TValue>
class node
{
 private:
   std::vector<std::shared_ptr<node<TValue>>> _children;
   TValue value;
   bool value_set;

   node() : value_set(false) {}
   node(TValue value) : value_set(true)
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
   TValue get() const
   {
      if (!value_set)
         throw tree_error("Node does not contain any value");
      return value;
   }
   void set(TValue value)
   {
      this->value = value;
      value_set = true;
   }

   // Children management
   std::shared_ptr<node<TValue>> add_child(TValue value)
   {
      auto node = make(value);
      add_child(node);
      return node;
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
   bool has_value() const noexcept { return value_set; }
};
} // namespace sanelli