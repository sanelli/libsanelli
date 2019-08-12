#pragma once

#include <utility>
#include <cmath>

namespace sanelli
{

template <typename T>
class fuzzy_variable
{
   T _value;

public:
   fuzzy_variable(const T value) : _value(value){};
   fuzzy_variable(const fuzzy_variable &other) : _value(other._value) {}
   fuzzy_variable(fuzzy_variable &&other) : _value(std::move(other._value)) {}

   fuzzy_variable &operator=(const fuzzy_variable &other)
   {
      if (this != &other)
         _value = other._value;
      return *this;
   }

   fuzzy_variable &operator=(fuzzy_variable &&other)
   {
      _value = std::move(other._value);
   }

   T value() const { return _value; }
};

template <typename TValue>
fuzzy_variable<TValue> make_fuzzy(TValue value)
{
   return fuzzy_variable(1 / (1 + std::exp(-value)));
}

} // namespace sanelli