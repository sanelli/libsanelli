#pragma once

#include <algorithm>
#include <iterator>
#include <functional>

namespace sanelli {

template<typename TInputIterator, typename TValue> 
size_t indexof(TInputIterator begin, TInputIterator end, TValue element) { 
   auto it = std::find(begin, end, element);
   if(it != end)
      return distance(it, end);
   return -1;
}

template<typename TInputIterator, typename TUnaryPredicate> 
size_t indexof_if(TInputIterator begin, TInputIterator end, TUnaryPredicate predicate) { 
   auto it = std::find_if(begin, end, predicate);
   if(it != end)
      return distance(it, end);
   return -1;
}

}