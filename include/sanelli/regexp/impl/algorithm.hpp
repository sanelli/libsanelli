#pragma once

// -- Recongnised grammar --
// E1 -> E1 '|' E2 | E2
// E2 -> E2 '&' E3 | E2 E3 | E3
// E3 -> TERM '*' | TERM '+' | TERM
// TERM -> letter | digit | symbol

// -- Grammar without the left recursion --
// E1 -> E2 R1
// R1 -> '|' E2 R1
// E2 -> E3 R2
// R2 -> '&' E3 R2 | E3 R2
// E3 -> TERM '*' | TERM '+' | TERM
// TERM -> letter | digit | symbol | ε | '(' E1 ')' | '[' character_class ']'

namespace sanelli::regexp
{

namespace impl
{
template <typename TChar, typename TInput>
class regexp_parser
{
   TChar lookahead;

 public:
   regexp_parser() {}
   void parse() {}
};

} // namespace impl

} // namespace sanelli::regexp