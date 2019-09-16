#pragma once

#include <type_traits>

namespace sanelli
{

// https://stackoverflow.com/a/4609795/1468832
template <typename T> inline constexpr
int sign(T x, std::false_type is_signed) {
    return T(0) < x;
}

template <typename T> inline constexpr
int sign(T x, std::true_type is_signed) {
    return (T(0) < x) - (x < T(0));
}

template <typename T> inline constexpr
int sign(T x) {
    return sign(x, std::is_signed<T>());
}

} // namespace sanelli