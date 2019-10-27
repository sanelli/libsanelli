#pragma once

#include <cmath>
#include <type_traits>
#include <stdexcept>

namespace sanelli
{

class binary_converter
{
public:
   // https://stackoverflow.com/a/8059809/1468832
   // https://en.wikipedia.org/wiki/Type_punning
   template <typename TNumericType>
   static size_t to_binary(TNumericType input, char output[], size_t start_at = 0, size_t max_size = sizeof(TNumericType))
   {

      static_assert(std::is_arithmetic<TNumericType>(), "An arithmentic (numeric) type is required.");

      union {
         TNumericType input;
         char output[sizeof(TNumericType)];
      } u = {.input = input};

      for (size_t index = 0; index < sizeof(TNumericType) && index < max_size; ++index)
         output[start_at + index] = u.output[index];

      return std::min(sizeof(TNumericType), max_size);
   }

   template <typename TNumericType>
   static TNumericType from_binary(char input[], size_t start_at = 0, size_t size = sizeof(TNumericType))
   {

      static_assert(std::is_arithmetic<TNumericType>(), "An arithmentic (numeric) type is required.");

      union {
         TNumericType output;
         char input[sizeof(TNumericType)];
      } u;

      for (size_t index = 0; index < std::min(sizeof(TNumericType), size); ++index)
         u.input[index] = input[start_at + index];

      return u.output;
   }

   template <typename TNumericType>
   static TNumericType from_binary(char input[], size_t *start_at, size_t size = sizeof(TNumericType))
   {
      if (start_at == nullptr)
         throw std::invalid_argument("start_at pointer cannot be null");

      auto result = from_binary<TNumericType>(input, *start_at, size);

      *start_at = *start_at + std::min(sizeof(TNumericType), size);

      return result;
   }
};

} // namespace sanelli