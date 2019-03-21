#pragma once

#include <iostream>
#include <utility>

namespace sanelli::debug
{

template <typename TContainer>
void printctr(const TContainer &container)
{
   for (auto it = std::begin(container); it != std::end(container); ++it)
      std::cout << *it << " ";
   std::cout << std::endl;
}

template <typename T>
void println(T t){
   std::cout << t << std::endl;
}

} // namespace sanelli::debug