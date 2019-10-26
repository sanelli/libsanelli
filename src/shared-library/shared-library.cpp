#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <stdexcept>

#include <sanelli/sanelli.hpp>

using namespace sanelli;

#if defined(__APPLE__)
#include <dlfcn.h>
#define NATIVE_DL_OPEN(name) dlopen(name, RTLD_NOW | RTLD_LOCAL)
#define NATIVE_DL_CLOSE(handle) dlclose(handle)
#define NATIVE_DL_SYMBOL(handle, symbol) dlsym(handle, symbol)
#else
#define NATIVE_DL_OPEN(name) nullptr
#define NATIVE_DL_CLOSE(handle)
#define NATIVE_DL_SYMBOL(handle, symbol) nullptr
#endif

shared_library::shared_library(std::string name, std::string path)
    : _name(name), _platform_name(path), _native_handle(nullptr)
{
   _native_handle = NATIVE_DL_OPEN(_platform_name.c_str());
   if (_native_handle == nullptr)
      throw std::runtime_error(sanelli::make_string("Unable to open native library '", _name, "' ('", _platform_name, "')"));
}

shared_library::~shared_library()
{
   if (_native_handle != nullptr)
      NATIVE_DL_CLOSE(_native_handle);
}

void *shared_library::get_native_handler(std::string symbol)
{
   return NATIVE_DL_SYMBOL(_native_handle, symbol.c_str());
}
