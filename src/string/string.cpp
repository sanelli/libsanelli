#include <algorithm>
#include <cctype>
#include <locale>
#include <string>

#include <sanelli/sanelli.hpp>

// https://stackoverflow.com/a/217605
int sanelli::ltrim(std::string &s)
{
   auto itBegin = s.begin();
   auto itEnd = std::find_if(s.begin(), s.end(), [](int ch) {
      return !std::isspace(ch);
   });
   s.erase(itBegin, itEnd);
   return itEnd - itBegin;
}

int sanelli::rtrim(std::string &s) {
    auto initial_length = s.length();
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return initial_length - s.length();
}
