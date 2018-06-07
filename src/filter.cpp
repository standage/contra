// -----------------------------------------------------------------------------
// Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
//
// This file is part of contra (http://github.com/standage/contra) and is
// licensed under the MIT license: see LICENSE.txt.
// -----------------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include <cmath>
#include <limits>
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

template<typename ElementType, typename CounterType>
filter<ElementType, CounterType>::filter() : buckets_occupied(0), table(0)
{
    // Default constructor. Do not use without subsequently calling `init`.
}

template<typename ElementType, typename CounterType>
filter<ElementType, CounterType>::filter(size_t total_size, size_t num_rows)
        : buckets_occupied(num_rows, 0),
          table(num_rows, std::vector<CounterType>())
{
    size_t target_row_size = total_size / num_rows;
    std::vector<size_t> row_sizes = get_primes(target_row_size, num_rows);
    for (size_t i = 0; i < row_sizes.size(); i++) {
        size_t size = row_sizes[i];
        table[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType>
filter<ElementType, CounterType>::filter(std::vector<size_t> row_sizes)
        : buckets_occupied(row_sizes.size(), 0),
          table(row_sizes.size(), std::vector<CounterType>())
{
    for (size_t i = 0; i < row_sizes.size(); i++) {
        size_t size = row_sizes[i];
        table[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType>
void filter<ElementType, CounterType>::insert(ElementType element)
{
    for (size_t i = 0; i < table.size(); i++){
        size_t index = element % table[i].size();
        if (table[i][index] == 0) {
            buckets_occupied[i] += 1;
        }
        if (table[i][index] < std::numeric_limits<CounterType>::max()) {
            table[i][index] = table[i][index] + 1;
        }
    }
}

template<typename ElementType, typename CounterType>
CounterType filter<ElementType, CounterType>::query(ElementType element)
{
    CounterType mincount;
    for (size_t i = 0; i < table.size(); i++) {
        size_t index = element % table[i].size();
        CounterType count = table[i][index];
        if (count == 0) {
            // No need to check other rows if any of them contain a 0
            return 0;
        }
        if (i == 0 || count < mincount) {
            mincount = count;
        }
    }
    return mincount;
}

template<typename ElementType, typename CounterType>
void filter<ElementType, CounterType>::init(std::vector<size_t> row_sizes)
{
    // If default constructor is used, init must be called subsequently.
    buckets_occupied.resize(row_sizes.size(), 0);
    table.resize(row_sizes.size(), std::vector<CounterType>());
    for (size_t i = 0; i < row_sizes.size(); i++) {
        size_t size = row_sizes[i];
        table[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType>
size_t filter<ElementType, CounterType>::size()
{
    size_t size = 0;
    for (auto const &row : this->table) {
        size += row.size();
    }
    return size;
}

template<typename ElementType, typename CounterType>
double filter<ElementType, CounterType>::estimate_fpr()
{
    // TODO!!!
    return 0.0;
}

template class filter<uint64_t, bool>;
template class filter<uint64_t, uint8_t>;
template class filter<uint64_t, uint32_t>;

} // namespace contra_cpp
