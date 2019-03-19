#pragma once

#include <stdexcept>

namespace sanelli::automa
{
class automa_error : public std::domain_error
{
 public:
   automa_error(const char *message) : domain_error(message) {}
   automa_error(const std::string &message) : domain_error(message) {}
};

} // namespace sanelli::tree