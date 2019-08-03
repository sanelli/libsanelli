#pragma once

#include <iostream>

// #define SANELLI_DEBUG_ENABLED

#define SANELLI_DEBUG_GET_MACRO(_1, _2, NAME, ...) NAME
#define SANELLI_DEBUG(...)                                        \
   SANELLI_DEBUG_GET_MACRO(__VA_ARGS__, SANELLI_DEBUG2, SANELLI_DEBUG1) \
   (__VA_ARGS__)

#ifdef SANELLI_DEBUG_ENABLED

#define SANELLI_DEBUG1(x) \
   {                   \
      std::cerr << x;  \
   }
#define SANELLI_DEBUG2(debugger, x)                                            \
   {                                                                           \
      if (sanelli::sanelli_debugger::is_debug_enabled(debugger))               \
      {                                                                        \
         std::cerr << x;                                                       \
      }                                                                        \
   }
#define SANELLI_INSTALL_DEBUGGER(debugger)                                     \
   {                                                                           \
      sanelli::sanelli_debugger::enabled_debug_for(debugger);                  \
   }
#else
#define SANELLI_DEBUG1(x)
#define SANELLI_DEBUG2(x,y)
#define SANELLI_INSTALL_DEBUGGER(debugger)
#endif

namespace sanelli
{
class sanelli_debugger
{
public:
   static void enabled_debug_for(const char *debugger);
   static bool is_debug_enabled(const char *debugger);
};
} // namespace sanelli
