#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include <sanelli/string/string.hpp>
#include <sanelli/debug/debug.hpp>
#include <sanelli/tokenizer/tokenizer.hpp>
#include <sanelli/parser/impl/parser_error.hpp>
#include <sanelli/parser/impl/parser_context.hpp>
#include <sanelli/parser/impl/parser_io.hpp>

namespace sanelli
{

template <typename TTokenType>
class parser
{
protected:
   static bool is_token(parser_context<TTokenType> &context, TTokenType token_type, unsigned long lookahead = 0)
   {
      if (!context.has_more_tokens(lookahead))
         return false;

      auto token = context.token(context.index() + lookahead);
      SANELLI_DEBUG("sanelli-parser", make_string("common_parser::is_token<expected=", token_type, ", actual=", token.type() , ", match=", (token.type() == token_type ? "yes": "no"),">") << std::endl);

      return token.type() == token_type;
   }

   static bool is_token_and_match(parser_context<TTokenType> &context, TTokenType token_type)
   {
      if (is_token(context, token_type))
      {
         match_token(context, token_type);
         return true;
      }
      return false;
   }

   static std::string match_token_and_get_value(parser_context<TTokenType> &context, TTokenType token_type)
   {
      if (!context.has_more_tokens())
         throw parser_error("No more tokens to parse.");

      auto token = context.peek_token();
      if (is_token(context, token_type))
      {
         SANELLI_DEBUG("sanelli-parser", make_string("common_parser::match_token_and_get_value<", token_type,">") << std::endl);

         auto value = token.value();
         context.move_next_token();
         return value;
      } else {
         auto message = sanelli::make_string("Unexpected token: was expecting '", token_type, "' but found '", token.type(), "'.");
         throw_parse_error_with_details(context, token.line(), token.column(), message);
      }
   }

   static void match_token(parser_context<TTokenType> &context, TTokenType token_type)
   {
      if (!context.has_more_tokens())
         throw parser_error("No more tokens to parse.");

      if (is_token(context, token_type))
      {
         SANELLI_DEBUG("sanelli-parser", make_string("common_parser::match_token<", token_type,">") << std::endl);
         context.move_next_token();
      } else {
         auto token = context.peek_token();
         auto message = sanelli::make_string("Unexpected token: was expecting '", token_type, "' but found '", token.type(), "'.");
         throw_parse_error_with_details(context, token.line(), token.column(), message);
      }
   }

public:
   [[noreturn]]
   static inline void throw_parse_error_with_details(const parser_context<TTokenType> &context, const unsigned int line, const unsigned int column, const std::string& message, unsigned int display_token = 5){
      SANELLI_DEBUG("sanelli-parser", make_string("common_parser::parser_error<", context.context_token_to_string(display_token), ">") << std::endl);
      throw parser_error(line, column, message);
   }

   [[noreturn]]
   static inline void throw_parse_error_with_details(const parser_context<TTokenType> &context, const std::string& message, unsigned int display_token = 5){
      SANELLI_DEBUG("sanelli-parser", make_string("common_parser::parser_error<", context.context_token_to_string(display_token), ">") << std::endl);
      throw parser_error(0,0,message);
   }
};
} // namespace sanelli