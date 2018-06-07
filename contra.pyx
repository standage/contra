# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

# distutils: language = c++
# distutils: sources = src/bstree.cpp src/filter.cpp
# cython: c_string_type=str, c_string_encoding=ascii

from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector
from libc.stdint cimport int32_t, uint32_t, uint64_t, uint8_t


cdef extern from "<iostream>" namespace "std":
    cdef cppclass ostream:
        ostream() except +

cdef extern from "<sstream>" namespace "std":
    cdef cppclass stringstream(ostream):
        stringstream() except +
        string str()

# Declare C++ interface

cdef extern from 'bstree.hpp' namespace 'contra_cpp':
    cdef cppclass bstree[T]:
        bstree() except +
        bool insert(T value)
        bool search(T value)
        void remove(T value)
        size_t height(T value)
        void inorder(ostream& stream)
        void preorder(ostream& stream)
        void postorder(ostream& stream)
        unsigned int size()

cdef extern from 'filter.hpp' namespace 'contra_cpp':
    cdef cppclass filter[E, C]:
        filter() except +
        filter(vector[size_t] array_sizes) except +
        void init(vector[size_t] array_sizes)
        void insert(E value)
        C query(E value)
        size_t size()
        double estimate_fpr()

    vector[size_t] get_primes(size_t target, size_t n)

# Declare Python implementation

cdef class BStree:
    cdef bstree[int32_t] tree
    def insert(self, int32_t value):
        return self.tree.insert(value)
    def search(self, int32_t value):
        return self.tree.search(value)
    def remove(self, int32_t value):
        return self.tree.remove(value)
    def height(self, int32_t value):
        return self.tree.height(value)
    def inorder(self):
        cdef stringstream ss
        self.tree.inorder(ss)
        return ss.str()
    def preorder(self):
        cdef stringstream ss
        self.tree.preorder(ss)
        return ss.str()
    def postorder(self):
        cdef stringstream ss
        self.tree.postorder(ss)
        return ss.str()
    def __repr__(self):
        return '<contra.BStree instance with {} values>'.format(len(self))
    def __str__(self):
        return self.inorder()
    def __len__(self):
        return self.tree.size()

cdef class BStreeLarge:
    cdef bstree[uint64_t] tree
    def insert(self, uint64_t value):
        return self.tree.insert(value)
    def search(self, uint64_t value):
        return self.tree.search(value)
    def remove(self, uint64_t value):
        return self.tree.remove(value)
    def height(self, uint64_t value):
        return self.tree.height(value)
    def inorder(self):
        cdef stringstream ss
        self.tree.inorder(ss)
        return ss.str()
    def preorder(self):
        cdef stringstream ss
        self.tree.preorder(ss)
        return ss.str()
    def postorder(self):
        cdef stringstream ss
        self.tree.postorder(ss)
        return ss.str()
    def __repr__(self):
        return '<contra.BStreeLarge instance with {} values>'.format(len(self))
    def __str__(self):
        return self.inorder()
    def __len__(self):
        return self.tree.size()

cdef class BStreeSmall:
    cdef bstree[uint8_t] tree
    def insert(self, uint8_t value):
        return self.tree.insert(value)
    def search(self, uint8_t value):
        return self.tree.search(value)
    def remove(self, uint8_t value):
        return self.tree.remove(value)
    def height(self, uint8_t value):
        return self.tree.height(value)
    def inorder(self):
        cdef stringstream ss
        self.tree.inorder(ss)
        return ss.str()
    def preorder(self):
        cdef stringstream ss
        self.tree.preorder(ss)
        return ss.str()
    def postorder(self):
        cdef stringstream ss
        self.tree.postorder(ss)
        return ss.str()
    def __repr__(self):
        return '<contra.BStreeSmall instance with {} values>'.format(len(self))
    def __str__(self):
        return self.inorder()
    def __len__(self):
        return self.tree.size()

cdef class BloomFilter:
    cdef filter[uint64_t, bool] bf;
    def __cinit__(self, size_t totalmem, int numhash=4):
        cdef size_t tablesize = totalmem * 8 / numhash
        cdef vector[size_t] as = get_primes(tablesize, numhash)
        self.bf.init(as)
    def insert(self, uint64_t value):
        self.bf.insert(value)
    def query(self, uint64_t value):
        return self.bf.query(value)
    def estimate_fpr(self):
        return self.bf.estimate_fpr()
    def __repr__(self):
        return '<contra.BloomFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.bf.size()

cdef class CountFilter:
    cdef filter[uint64_t, uint8_t] cf;
    def __cinit__(self, size_t totalmem, int numhash=4):
        cdef size_t tablesize = totalmem / numhash
        cdef vector[size_t] as = get_primes(tablesize, numhash)
        self.cf.init(as)
    def insert(self, uint64_t value):
        self.cf.insert(value)
    def query(self, uint64_t value):
        return self.cf.query(value)
    def estimate_fpr(self):
        return self.cf.estimate_fpr()
    def __repr__(self):
        return '<contra.CountFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.cf.size()

cdef class BigCountFilter:
    cdef filter[uint64_t, uint32_t] bcf;
    def __cinit__(self, size_t totalmem, int numhash=4):
        cdef size_t tablesize = totalmem / 4 / numhash
        cdef vector[size_t] as = get_primes(tablesize, numhash)
        self.bcf.init(as)
    def insert(self, uint64_t value):
        self.bcf.insert(value)
    def query(self, uint64_t value):
        return self.bcf.query(value)
    def estimate_fpr(self):
        return self.bcf.estimate_fpr()
    def __repr__(self):
        return '<contra.BigCountFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.bcf.size()
