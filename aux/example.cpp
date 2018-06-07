#include <iostream>
#include <vector>
#include "bstree.hpp"
#include "filter.hpp"

using namespace contra_cpp;

int main()
{
    bstree<int> tree;
    std::vector<int> values = {2, 32, 95, 71, -36, -35, -27, -19, 9, -82};
    for (auto v : values) {
        tree.insert(v);
    }
    tree.inorder();

    CountFilter cf(100, 2);
    cf.insert(5);

    return 0;
}
