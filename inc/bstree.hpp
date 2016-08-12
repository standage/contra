#ifndef CONTRA_BS_TREE
#define CONTRA_BS_TREE

#include <iostream>
#include <ostream>
#include "node.hpp"

namespace contra_cpp
{

class bstree
{
    public:
        bstree() : _root(nullptr), _count(0) {}

        bool insert(int value);
        bool search(int value);
        void remove(int value);
        unsigned int size();
        int height(int value);

        void inorder(std::ostream& stream = std::cout);
        void preorder(std::ostream& stream = std::cout);
        void postorder(std::ostream& stream = std::cout);

    protected:
        nodeptr _root;
        unsigned int _count;

        bool insert(nodeptr& root, int value, int height);
        bool search(nodeptr& root, int value);
        nodeptr remove(nodeptr& root, int value, bool decr = true);
        nodeptr minimum(nodeptr& root);
        int height(nodeptr& root, int value);
        void decr_height(nodeptr& root);

        void inorder(nodeptr& root, std::ostream& stream);
        void preorder(nodeptr& root, std::ostream& stream);
        void postorder(nodeptr& root, std::ostream& stream);

}; // class bstree

} // namespace contra_cpp

#endif // define CONTRA_BS_TREE
