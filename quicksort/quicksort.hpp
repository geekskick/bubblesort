#pragma once

#include <array>

template<typename Container>
typename Container::iterator partition(typename Container::iterator begin, typename Container::iterator end){
    const auto pivot = *std::prev(end); 
    auto i = begin - 1;
    for(auto j = begin; j < end-1; ++j){
        if(*j <= pivot){
            i++;
            std::swap(*i, *j);
        }
    }
    std::swap(*std::next(i), *std::prev(end));
    return std::next(i);
}

template<typename Container>
void quicksort_inplace(typename Container::iterator begin, typename Container::iterator end){
    if(begin < end - 1){
        const auto p = partition<Container>(begin, end);
        quicksort_inplace<Container>(begin, p);
        quicksort_inplace<Container>(p, end);
    }
}

template<typename T, size_t Len>
std::array<T, Len> quicksort(const std::array<T, Len>& unsorted){
    auto rc = unsorted;
    quicksort_inplace<std::array<T, Len>>(rc.begin(), rc.end());
    return rc;
}

template<typename Container>
Container quicksort(const Container& unsorted){
    auto rc = unsorted;
    quicksort_inplace<Container>(rc.begin(), rc.end());
    return rc;
}
