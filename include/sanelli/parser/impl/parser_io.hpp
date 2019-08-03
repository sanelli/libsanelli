#pragma once

#include <stdexcept>

#include <sanelli/parser/impl/parser_context.hpp>

namespace sanelli
{

template <typename TTokenType>
std::ostream &operator<<(std::ostream &os, const parser_context<TTokenType> &context)
{
   return os << context._tokens;
}

}