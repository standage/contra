#include <assert.h>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <vector>
#include "bstree.hpp"

using namespace contra_cpp;

int main(int argc, const char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " n [random seed]" << std::endl;
        return 0;
    }

    unsigned int n = atoi(argv[1]);
    assert(n >= 10);
    unsigned int seed;
    if (argc > 2) {
        seed = atoi(argv[2]);
    }
    else {
        seed = time(NULL);
    }
    std::cerr << "random seed: " << seed << std::endl;
    srand(seed);

    bstree tree;
    assert(tree.size() == 0);
    int r;
    std::vector<int> v;
    for(unsigned int i = 0; i < n; i++) {
        r = rand() % 3100000000;
        if (!tree.search(r)){
            tree.insert(r);
            if (v.size() < 10) {
                v.push_back(r);
            }
        }
    }
    assert(tree.size() == n);
    tree.remove(r);
    assert(tree.size() == n - 1);
    while (!v.empty()) {
        int i = v.back();
        v.pop_back();
        tree.remove(i);
    }
    assert(tree.size() == n - 11);
    tree.inorder();

    return 0;
}
