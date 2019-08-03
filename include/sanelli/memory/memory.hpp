#pragma once

#include <memory>

namespace sanelli {
   class memory {
      public:
      template<typename TResult, typename... TParams>
      static std::shared_ptr<TResult> make_shared(TParams... args) {
         return std::shared_ptr<TResult>(new TResult(args...));
      }
   };
}
