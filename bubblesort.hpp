#pragma once

#include <array>

template<typename T, typename ... Args>
constexpr std::array<T, sizeof...(Args)> make_array(Args&& ... args){
    return {std::forward<Args>(args)...};

}

template<typename Container>
void bubblesort_inplace(typename Container::iterator begin, typename Container::iterator end){
    while(!std::is_sorted(begin, end)){
        for(auto it = begin; it != end - 1; ++it){
            auto next = std::next(it);
            if(*it > *next){
                std::swap(*it, *next);
            }
        }
    }
}

template<typename T, size_t Len>
std::array<T, Len> bubblesort(const std::array<T, Len>& unsorted){
    auto rc = unsorted;
    bubblesort_inplace<std::array<T, Len>>(rc.begin(), rc.end());
    return rc;
}

template<typename Container>
Container bubblesort(const Container& unsorted){
    auto rc = unsorted;
    bubblesort_inplace<Container>(rc.begin(), rc.end());
    return rc;
}