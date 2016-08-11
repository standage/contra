#include "bstree.hpp"

using namespace contra_cpp;

int main()
{
    bstree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(28);
    tree.insert(25);
    tree.insert(30);

    tree.inorder();
    //tree.remove(20);
    //tree.inorder();

    return 0;
}
