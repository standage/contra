// -----------------------------------------------------------------------------
// Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
//
// This file is part of contra (http://github.com/standage/contra) and is
// licensed under the MIT license: see LICENSE.txt.
// -----------------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include <cmath>
#include "filter.hpp"

namespace contra_cpp
{

static inline bool isprime(size_t n)
{
    assert(n >= 0);
    if (n == 1) {
        return false;
    }
    else if (n == 2) {
        return true;
    }
    else if (n % 2 == 0) {
        return true;
    }
    for (int i = 3; i < pow(n, 0.5) + 1; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

std::vector<size_t> get_primes(size_t target, size_t n)
{
    std::vector<size_t> primes;
    if (target == 1 && n == 1) {
        primes.push_back(1);
        return primes;
    }
    int i = target - 1;
    if (i % 2 == 0) {
        i--;
    }
    while (primes.size() < n && i > 0) {
        if (isprime(i)) {
            primes.push_back(i);
        }
        i -= 2;
    }
    assert(primes.size() == n);
    return primes;
}

template<typename ElementType, typename CounterType, size_t maxcount>
filter<ElementType, CounterType, maxcount>::filter(std::vector<size_t> array_sizes)
        : _cells_occupied(array_sizes.size(), 0),
          _arrays(array_sizes.size(), std::vector<CounterType>())
{
    for (size_t i = 0; i < array_sizes.size(); i++) {
        size_t size = array_sizes[i];
        _arrays[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType, size_t maxcount>
filter<ElementType, CounterType, maxcount>::filter()
{
    // Default constructor, for convenience at the Cython/Python interface only.
}

template<typename ElementType, typename CounterType, size_t maxcount>
void filter<ElementType, CounterType, maxcount>::init(std::vector<size_t> array_sizes)
{
    // If default constructor is used, init must be called subsequently.
    _cells_occupied.resize(array_sizes.size(), 0);
    _arrays.resize(array_sizes.size(), std::vector<CounterType>());
    for (size_t i = 0; i < array_sizes.size(); i++) {
        size_t size = array_sizes[i];
        _arrays[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType, size_t maxcount>
filter<ElementType, CounterType, maxcount>::filter(size_t total_size, size_t num_arrays)
        : _cells_occupied(num_arrays, 0),
          _arrays(num_arrays, std::vector<CounterType>())
{
    size_t target_table_size = total_size / num_arrays;
    std::vector<size_t> array_sizes = get_primes(target_table_size, num_arrays);
    for (size_t i = 0; i < array_sizes.size(); i++) {
        size_t size = array_sizes[i];
        _arrays[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType, size_t maxcount>
void filter<ElementType, CounterType, maxcount>::add(ElementType element)
{
    for (size_t i = 0; i < _arrays.size(); i++){
        size_t index = element % _arrays[i].size();
        if (_arrays[i][index] == 0) {
            _cells_occupied[i] += 1;
        }
        if (_arrays[i][index] < maxcount) {
            _arrays[i][index] = _arrays[i][index] + 1;
        }
    }
}

template<typename ElementType, typename CounterType, size_t maxcount>
CounterType filter<ElementType, CounterType, maxcount>::get(ElementType element)
{
    CounterType mincount = _arrays[0][element % _arrays[0].size()];
    for (auto array : _arrays) {
        size_t index = element % array.size();
        CounterType count = array[index];
        if (count == 0) {
            // No need to check other arrays if any of them contain a 0
            return 0;
        }
        if (count < mincount) {
            mincount = count;
        }
    }
    return mincount;
}

template<typename ElementType, typename CounterType, size_t maxcount>
size_t filter<ElementType, CounterType, maxcount>::size()
{
    size_t size = 0;
    for (auto array : this->_arrays) {
        std::cerr << "Yo: " << array.size() << '\n';
        size += array.size();
    }
    return size;
}

template<typename ElementType, typename CounterType, size_t maxcount>
double filter<ElementType, CounterType, maxcount>::estimate_fpr()
{
    // TODO!!!
    return 0.0;
}

template class filter<uint64_t, bool, 1>;
template class filter<uint64_t, uint8_t, 255>;
template class filter<uint64_t, uint32_t, 8589934591>;

} // namespace contra_cpp
