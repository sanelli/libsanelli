#pragma once

#include <string>
#include <stdexcept>


namespace sanelli {

class tokenizer_error : public std::domain_error
{
   int _line;
   int _column;

public:
   tokenizer_error(int line, int column, const char *message) : domain_error(message), _line(line), _column(column) {}
   tokenizer_error(int line, int column, const std::string &message) : domain_error(message), _line(line), _column(column) {}

   int line() const { return _line; }
   int column() const { return _column; }
};
}