#pragma once

#include <cmath>

#include <sanelli/fuzzy/impl/variable.hpp>

namespace sanelli {

template <typename T>
fuzzy_variable<T> zero() { return fuzzy_variable((T)0); }

template <typename T>
fuzzy_variable<T> one() { return fuzzy_variable((T)1); }

template <typename T>
bool operator==(const fuzzy_variable<T>& lhs, const fuzzy_variable<T>& rhs){ 
   return lhs.value() == rhs.value();
}

template <typename T>
bool operator!=(const fuzzy_variable<T>& lhs, const fuzzy_variable<T>& rhs){ 
   return !(lhs == rhs);
}

template <typename T>
fuzzy_variable<T> operator&&(const fuzzy_variable<T>& lhs, const fuzzy_variable<T>& rhs){ 
   return fuzzy_variable<T>((T)std::min(lhs.value(), rhs.value()));
}

template <typename T>
fuzzy_variable<T> operator||(const fuzzy_variable<T>& lhs, const fuzzy_variable<T>& rhs){ 
   return fuzzy_variable<T>((T)std::max(lhs.value(), rhs.value()));
}

template <typename T>
fuzzy_variable<T> operator!(const fuzzy_variable<T>& variable){ 
   return fuzzy_variable<T>((T)1 - variable.value());
}

}