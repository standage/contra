#include "avltree.hpp"

using namespace dss_avl_tree;

int main()
{
    AVLtree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(28);
    tree.insert(25);
    tree.insert(30);

    tree.inorder();
    tree.remove(20);
    tree.inorder();

    return 0;
}
