// -----------------------------------------------------------------------------
// Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
//
// This file is part of contra (http://github.com/standage/contra) and is
// licensed under the MIT license: see LICENSE.txt.
// -----------------------------------------------------------------------------

#ifndef CONTRA_FILTER
#define CONTRA_FILTER

#include <vector>

namespace contra_cpp
{

/**
 * Compute `n` distinct prime numbers near but less than `target`.
 */
std::vector<size_t> get_primes(size_t target, size_t n);

/**
 * Probabilistic filter for approximate set membership and abundance queries.
 *
 * Primary operations are `insert` to increment the count of an element, and
 * `query` to estimate the element's abundance. Accuracy of the estimates
 * depends on the number of buckets in the table and the number of distinct
 * elements being stored and queried.
 *
 * Instantiate with `CounterType=bool` for presence/absence queries (Bloom
 * filter) or with `CounterType=uint8_t` (or a larger unsigned integer type) for
 * abundance queries (Count-min sketch). The `BloomFilter` and `CountFilter`
 * typedefs are provided for convenience.
 *
 * Under the hood, this class is implemented as a table of counters with `d`
 * rows, each row containing approximately `w` columns. Each row should have a
 * different length, and each row length should be a prime number.
 */
template<typename ElementType, typename CounterType>
class filter
{
    public:
        /**
         * Constructors
         *
         * This class implements 3 constructors.
         *
         * - The first is the default constructor and is not intended for human
         *   consumption. It is for convenience when working Cython only.
         * - The second accepts the total number of buckets desired in the table
         *   as well as the number of rows.
         * - The third accepts an explicitly specified number of buckets for
         *   each row in the table.
         */
        filter();
        explicit filter(size_t total_size, size_t num_rows = 4);
        explicit filter(std::vector<size_t> row_sizes);

        /**
         * Primary operations
         *
         * - insert: store the element by hashing it for each row and
         *           incrementing the corresponding counters
         * - query: determine the count of the element by hashing it, checking
         *          the corresponding counters in each row, and returning the
         *          lowest observed count
         */
        void insert(ElementType element);
        CounterType query(ElementType element);

        // Ancillary methods
        void init(std::vector<size_t> row_sizes);  // (re-)initialize the table
        size_t size();                             // total number of buckets/counters in the table
        double estimate_fpr();                     // estimate the table's current false positive rate
        void savefile(std::string& filename);      // save to a file
        void loadfile(std::string& filename);      // load from a file

        template<class Archive>
        inline void load(Archive & ar) {
            ar(buckets_occupied, table);
        }

        template<class Archive>
        inline void save(Archive &ar) const {
            ar(buckets_occupied, table);
        }

    protected:
        std::vector<size_t> buckets_occupied;
        std::vector<std::vector<CounterType>> table;
};

typedef filter<uint64_t, bool> BloomFilter;
typedef filter<uint64_t, uint8_t> CountFilter;
typedef filter<uint64_t, uint32_t> BigCountFilter;

} // namespace contra_cpp

#endif // define CONTRA_FILTER
