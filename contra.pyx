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

# Cython doesn't support integer template instantiation directly
# See https://groups.google.com/forum/#!topic/cython-users/xAZxdCFw6Xs
cdef extern from *:
    ctypedef int Int1 "1"
    ctypedef int Int255 "255"
    ctypedef int IntBig "8589934591"

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
    cdef cppclass filter[E, C, M]:
        filter() except +
        filter(vector[size_t] array_sizes) except +
        void init(vector[size_t] array_sizes)
        void add(E value)
        C get(E value)
        size_t size()
        double estimate_fpr()

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
    cdef filter[uint64_t, bool, Int1] bf;
    def __cinit__(self, list array_sizes):
        cdef vector[size_t] as = array_sizes
        self.bf.init(as)
    def add(self, uint64_t value):
        self.bf.add(value)
    def get(self, uint64_t value):
        return self.bf.get(value)
    def estimate_fpr(self):
        return self.bf.estimate_fpr()
    def __repr__(self):
        return '<contra.BloomFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.bf.size()

cdef class CountFilter:
    cdef filter[uint64_t, uint8_t, Int255] cf;
    def __cinit__(self, list array_sizes):
        cdef vector[size_t] as = array_sizes
        self.cf.init(as)
    def add(self, uint64_t value):
        self.cf.add(value)
    def get(self, uint64_t value):
        return self.cf.get(value)
    def estimate_fpr(self):
        return self.cf.estimate_fpr()
    def __repr__(self):
        return '<contra.CountFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.cf.size()

cdef class BigCountFilter:
    cdef filter[uint64_t, uint32_t, IntBig] bcf;
    def __cinit__(self, list array_sizes):
        cdef vector[size_t] as = array_sizes
        self.bcf.init(as)
    def add(self, uint64_t value):
        self.bcf.add(value)
    def get(self, uint64_t value):
        return self.bcf.get(value)
    def estimate_fpr(self):
        return self.bcf.estimate_fpr()
    def __repr__(self):
        return '<contra.BigCountFilter instance with {} buckets>'.format(len(self))
    def __len__(self):
        return self.bcf.size()
