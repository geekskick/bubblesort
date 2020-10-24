#pragma once

#include <array>

template<typename T, typename ... Args>
constexpr std::array<T, sizeof...(Args)> make_array(Args&& ... args){
    return {std::forward<Args>(args)...};
}

