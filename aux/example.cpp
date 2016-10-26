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

    std::vector<size_t> array_sizes = {97, 91};
    filter<uint64_t, uint8_t, 255> cf(array_sizes);
    cf.add(5);

    return 0;
}
