#ifndef DSS_BS_TREE
#define DSS_BS_TREE

#include <iostream>
#include <ostream>
#include "node.hpp"

namespace dss
{

class BStree
{
    public:
        BStree() : _root(nullptr), _count(0) {}

        bool insert(int value);
        bool search(int value);
        void remove(int value);
        unsigned int size();

        void inorder(std::ostream& stream = std::cout);
        void preorder(std::ostream& stream = std::cout);
        void postorder(std::ostream& stream = std::cout);

    protected:
        nodeptr _root;
        unsigned int _count;

        bool insert(nodeptr& root, int value, int height);
        bool search(nodeptr& root, int value);
        nodeptr remove(nodeptr& root, int value);
        nodeptr minimum(nodeptr& root);

        void inorder(nodeptr& root, std::ostream& stream);
        void preorder(nodeptr& root, std::ostream& stream);
        void postorder(nodeptr& root, std::ostream& stream);

}; // class BStree

} // namespace dss

#endif // define DSS_BS_tree
