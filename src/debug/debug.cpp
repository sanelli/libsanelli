#include <set>
#include <cstring>
#include <sanelli/debug/debug.hpp>

static std::set<const char*> __sanelli_enabled_debuggers = { };
void sanelli::sanelli_debugger::enabled_debug_for(const char* debugger)
{
   __sanelli_enabled_debuggers.insert(debugger);
}

bool sanelli::sanelli_debugger::is_debug_enabled(const char* debugger)
{
   for(auto it = __sanelli_enabled_debuggers.begin(); it != __sanelli_enabled_debuggers.end(); ++it)
   {
      const char* value = *it;
      if(strcmp(debugger, value)==0)
         return true;
   }
   return false;
}