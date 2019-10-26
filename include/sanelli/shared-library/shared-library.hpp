#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <type_traits>

#include <sanelli/memory/memory.hpp>

namespace sanelli
{

class shared_library
{
   std::string _name;
   std::string _platform_name;
   void *_native_handle;
   shared_library(std::string name, std::string path);

protected:
   void *get_native_handler(std::string symbol);

public:
   ~shared_library();

   friend sanelli::memory;
};

template <typename TLibraryType>
class shared_library_loader
{

   static_assert(std::is_base_of<shared_library, TLibraryType>(), "sanelli::shared_library_load library must be a subclass of sanelli::shared_library");

   std::map<std::string, std::shared_ptr<shared_library>> _libraries;
   std::function<std::string(std::string)> _format_library_name;

   bool has_library(std::string library) const
   {
      return _libraries.count(library) > 0;
   }

   void load_library(std::string library)
   {
      if (has_library(library))
         return;
      auto path = library;
      if (_format_library_name != nullptr)
         path = _format_library_name(path);
      _libraries[library] = sanelli::memory::make_shared<TLibraryType>(library, path);
   }

protected:
   shared_library_loader(std::function<std::string(std::string)> format_library_name)
       : _format_library_name(format_library_name)
   {
   }

public:
   ~shared_library_loader()
   {
      _libraries.clear();
   }
   std::shared_ptr<TLibraryType> get_library(std::string library)
   {
      if (!has_library(library))
         load_library(library);
      return std::dynamic_pointer_cast<TLibraryType>(_libraries[library]);
   }
   void libraries(std::vector<std::string> &libs) const
   {
      libs.clear();
      for (auto it = _libraries.begin(); it != _libraries.end(); ++it)
         libs.push_back(it->first);
   }

   friend sanelli::memory;
};

} // namespace sanelli