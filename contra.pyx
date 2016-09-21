# distutils: language = c++
# distutils: sources = src/bstree.cpp
# cython: c_string_type=str, c_string_encoding=ascii
# cython: linetrace=True
# distutils: define_macros=CYTHON_TRACE=1

from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "<iostream>" namespace "std":
    cdef cppclass ostream:
        ostream() except +

cdef extern from "<sstream>" namespace "std":
    cdef cppclass stringstream(ostream):
        stringstream() except +
        string str()

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

cdef class BStree:
    cdef bstree[long int] tree
    def insert(self, long int value):
        return self.tree.insert(value)
    def search(self, long int value):
        return self.tree.search(value)
    def remove(self, long int value):
        return self.tree.remove(value)
    def height(self, long int value):
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
