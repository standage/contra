# distutils: language = c++
# distutils: sources = src/bstree.cpp

from libcpp cimport bool

cdef extern from 'bstree.hpp' namespace 'dss':
    cdef cppclass BStree:
        BStree() except +
        bool insert(int value)
        bool search(int value)
        void remove(int value)
        void inorder()
        void preorder()
        void postorder()
        unsigned int size()

cdef class bstree:
    cdef BStree tree
    def insert(self, int value):
        return self.tree.insert(value)
    def search(self, int value):
        return self.tree.search(value)
    def remove(self, int value):
        return self.tree.remove(value)
    @property
    def size(self):
        return self.tree.size()
