#include <catch2/catch.hpp>
#include <string>

#include <sanelli/tokenizer/tokenizer.hpp>
#include <sanelli/parser/parser.hpp>

namespace sanelli {
   template<typename T>
   class test_parser : public sanelli::parser<T>{ 
      public:
         bool test_is_token(parser_context<T> &context, T token_type){
            return sanelli::parser<T>::is_token(context, token_type);
         }
         bool test_is_token_and_match(parser_context<T> &context, T token_type){
            return sanelli::parser<T>::is_token_and_match(context, token_type);
         }
         std::string test_match_token_and_get_value(parser_context<T> &context, T token_type){
            return sanelli::parser<T>::match_token_and_get_value(context, token_type);
         }
         void test_match_token(parser_context<T> &context, T token_type){
            sanelli::parser<T>::match_token(context, token_type);
         }
   };
   template<typename T>
   class test_context : public sanelli::parser_context<T> { };
}

SCENARIO("Parser", "[parser]"){

   sanelli::tokenizer<unsigned int> tokenizer;
   sanelli::test_parser<unsigned int> parser;
   sanelli::test_context<unsigned int> context;
   
    GIVEN("A set of rules"){

       tokenizer.add(1, "a", true, true);
       tokenizer.add(2, "b", true, true);
       tokenizer.add(3, "c", true, true);

       WHEN("Parsing rules") {
         std::string input("a b a a c c");

         tokenizer.tokenize(input, 0, context);
         auto result = parser.test_is_token(context, 1);
         REQUIRE(result);
         result = parser.test_is_token(context, 3);
         REQUIRE(!result);
         parser.test_is_token_and_match(context, 1);
         auto value = parser.test_match_token_and_get_value(context, 2);
         REQUIRE(value == "b");
         parser.test_match_token(context, 1);
       }
    }
}