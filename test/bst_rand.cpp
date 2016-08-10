#include <iostream>
#include <ostream>
#include <stdlib.h>
#include "bstree.hpp"

using namespace dss;

int main(int argc, const char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " n [random seed]" << std::endl;
        return 0;
    }

    unsigned int n = atoi(argv[1]);
    unsigned int seed;
    if (argc > 2) {
        seed = atoi(argv[2]);
    }
    else {
        seed = time(NULL);
    }
    std::cerr << "random seed: " << seed << std::endl;
    srand(seed);

    BStree tree;
    for(unsigned int i = 0; i < n; i++) {
        int r = rand() % 3100000000;
        tree.insert(r);
    }
    tree.inorder();

    return 0;
}
