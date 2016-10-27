// -----------------------------------------------------------------------------
// Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
//
// This file is part of contra (http://github.com/standage/contra) and is
// licensed under the MIT license: see LICENSE.txt.
// -----------------------------------------------------------------------------

#ifndef CONTRA_FILTER
#define CONTRA_FILTER

#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace contra_cpp
{

template<typename ElementType, typename CounterType, size_t maxcount>
class filter
{
    public:
        filter();
        explicit filter(std::vector<size_t> array_sizes);
        explicit filter(size_t total_size, size_t num_tables = 4);
        void init(std::vector<size_t> array_sizes);
        void add(ElementType element);
        CounterType get(ElementType element);
        size_t size();
        double estimate_fpr();

    protected:
        std::vector<size_t> _cells_occupied;
        std::vector<std::vector<CounterType>> _arrays;
};

} // namespace contra_cpp

#endif // define CONTRA_FILTER
