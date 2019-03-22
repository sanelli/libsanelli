#pragma once

#include <stdexcept>

namespace sanelli::string
{
class string_error : public std::domain_error
{
 public:
   string_error(const char *message) : domain_error(message) {}
   string_error(const std::string &message) : domain_error(message) {}
};

} // namespace sanelli::string