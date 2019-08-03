#pragma once

#include <string>
#include <sstream>

namespace sanelli
{

int ltrim(std::string &s);
int rtrim(std::string &s);

template <typename TArg>
inline void __make_string(std::stringstream &stream, const TArg &arg)
{
   stream << arg;
}

template <typename TArg, typename... TArgs>
inline void __make_string(std::stringstream &stream, const TArg &arg, const TArgs &... args)
{
   stream << arg;
   __make_string(stream, args...);
}

template <typename... TArgs>
std::string make_string(const TArgs &... args)
{
   std::stringstream stream;
   __make_string(stream, args...);
   return stream.str();
}

} // namespace sanelli