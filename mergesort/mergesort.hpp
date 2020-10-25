#pragma once

#include <array>
#include <limits>
#include <deque>

namespace{
    template<typename Container>
    void merge(const typename Container::iterator begin, const typename Container::iterator q, const typename Container::iterator end){
        using vt = typename Container::value_type;
        auto left = std::deque<vt>(begin, q);
        auto right = std::deque<vt>(q, end);
        left.emplace_back(std::numeric_limits<vt>::max());
        right.emplace_back(std::numeric_limits<vt>::max());
        for(auto k = 0; k < std::distance(begin, end); k++){
            if(left.front() <= right.front()){
                *std::next(begin, k) = left.front();
                left.pop_front();
            }
            else{
                *std::next(begin, k) = right.front();
                right.pop_front();
            }
        }
    }
}

template<typename Container>
void mergesort(typename Container::iterator begin, typename Container::iterator end){
    if(begin < end - 1){
        const auto q = std::next(begin, std::distance(begin, end)/2);
        mergesort<Container>(begin, q);
        mergesort<Container>(q, end);
        merge<Container>(begin, q, end);
    }
}

template<typename T, size_t Len>
std::array<T, Len> mergesort(const std::array<T, Len>& unsorted){
    auto rc = unsorted;
    mergesort<std::array<T, Len>>(rc.begin(), rc.end());
    return rc;
}

template<typename Container>
Container mergesort(const Container& unsorted){
    auto rc = unsorted;
    mergesort<Container>(rc.begin(), rc.end());
    return rc;
}
