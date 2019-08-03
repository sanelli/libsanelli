#pragma once

#include <stdexcept>

namespace sanelli
{
class tree_error : public std::domain_error
{
 public:
   tree_error(const char *message) : domain_error(message) {}
   tree_error(const std::string &message) : domain_error(message) {}
};

} // namespace sanelli