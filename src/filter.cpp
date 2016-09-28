// -----------------------------------------------------------------------------
// Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
//
// This file is part of contra (http://github.com/standage/contra) and is
// licensed under the MIT license: see LICENSE.txt.
// -----------------------------------------------------------------------------

#include "filter.hpp"

namespace contra_cpp
{

template<typename ElementType, typename CounterType, size_t maxcount>
filter<ElementType, CounterType, maxcount>::filter(std::vector<size_t> array_sizes)
        : _arrays(array_sizes.size(), std::vector<CounterType>())
{
    for (size_t i = 0; i < array_sizes.size(); i++) {
        size_t size = array_sizes[i];
        _arrays[i].resize(size, 0);
    }
}

template<typename ElementType, typename CounterType, size_t maxcount>
void filter<ElementType, CounterType, maxcount>::add(ElementType element)
{
    for (auto array : _arrays) {
        size_t index = element % array.size();
        if (array[index] < maxcount) {
            array[index] = array[index] + 1;
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
        if (count < mincount) {
            mincount = count;
        }
    }
    return mincount;
}

template<typename ElementType>
bool bloomfilter<ElementType>::get(ElementType element)
{
    for (auto array : this->_arrays) {
        size_t index = element % array.size();
        if (array[index] == false) {
            return false;
        }
    }
    return true;
}

template class filter<uint64_t, bool, 1>;
template class filter<uint64_t, uint8_t, 255>;
template class filter<uint64_t, uint32_t, 8589934591>;

} // namespace contra_cpp
