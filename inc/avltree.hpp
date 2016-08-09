#ifndef DSS_AVL_TREE
#define DSS_AVL_TREE

#include <iostream>
#include <memory>
#include <ostream>

namespace dss_avl_tree
{

class AVLtree
{
    public:
        struct AVLnode
        {
            std::unique_ptr<AVLnode> left;
            std::unique_ptr<AVLnode> right;
            int data;

            AVLnode(int value) : left(nullptr), right(nullptr), data(value) {}
        };
        typedef std::unique_ptr<AVLnode> nodeptr;

        AVLtree() : _root(nullptr) {}

        void insert(int value);
        bool search(int value);
        void remove(int value);

        void inorder(std::ostream& stream = std::cout);
        void preorder(std::ostream& stream = std::cout);
        void postorder(std::ostream& stream = std::cout);

    protected:
        nodeptr _root;

        void insert(nodeptr& root, int value);
        bool search(nodeptr& root, int value);
        nodeptr remove(nodeptr& root, int value);
        nodeptr minimum(nodeptr& root);

        void inorder(nodeptr& root, std::ostream& stream);
        void preorder(nodeptr& root, std::ostream& stream);
        void postorder(nodeptr& root, std::ostream& stream);

}; // end class AVLtree

} // end namespace dss_avl_tree

#endif // define DSS_AVL_tree
