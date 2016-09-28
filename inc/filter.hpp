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
        explicit filter(std::vector<size_t> array_sizes);
        void add(ElementType element);
        CounterType get(ElementType element);

    protected:
        std::vector<std::vector<CounterType>> _arrays;

};

template<typename ElementType>
class bloomfilter : public filter<ElementType, bool, 1>
{
    public:
        bool get(ElementType element);

    protected:
        std::vector<std::vector<bool>> _arrays;
};
template<typename ElementType> class countfilter : public filter<ElementType, uint8_t, 255> {};
template<typename ElementType> class bigcountfilter : public filter<ElementType, uint32_t, 8589934591> {};

} // namespace contra_cpp

#endif // define CONTRA_BS_TREE
