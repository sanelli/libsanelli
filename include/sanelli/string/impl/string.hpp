#pragma once

#include <string>
#include <sanelli/string/impl/exception.hpp>
#include <set>

namespace sanelli::string
{

template <typename TChar, typename TIterator, typename InserterIterator>
void expand_character_class(TIterator first, TIterator last, InserterIterator inserter)
{
   const TChar dash = (TChar)'-';
   const TChar slash = (TChar)'\\';
   const TChar right_par = (TChar)']';

   TChar last_char = (TChar)'\0';

   for (auto it = first; it != last; ++it)
   {
      bool escape = false;
      auto next_char = *it;
      if (next_char == slash)
      {
         ++it; // Move to next char
         next_char = *it;
         if (next_char != right_par)
            throw string_error("malformed character class - only ']' can be escaped.");
         escape = true;
      }

      if (next_char == dash && !escape)
      {
         if (last_char == (TChar)'\0')
            throw string_error("malformed character class - charcater class cannot start with dash.");
         ++it;
         if (it == last)
            throw string_error("malformed character class - unexpectedly terminated sequence after dash");
         auto end_char = *it;
         if (end_char <= last_char)
            throw string_error("malformed character class - character set borders must be increasing.");
         for (auto c = last_char + 1; c <= end_char; ++c)
            *(inserter++) = c;
      }
      else
      {
         *(inserter++) = next_char;
         last_char = next_char;
      }
   }
}

} // namespace sanelli::string