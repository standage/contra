#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "bstree.hpp"

using namespace contra_cpp;
typedef std::vector<int> vint;
typedef std::vector<std::string> vstring;

void test(vint& values, vstring& trav1, int to_remove, vstring& trav2)
{
    bstree tree;
    for (auto i : values) {
        tree.insert(i);
    }

    std::ostringstream io, pre, post;
    tree.inorder(io);
    tree.preorder(pre);
    tree.postorder(post);
    assert(io.str() == trav1[0]);
    assert(pre.str() == trav1[1]);
    assert(post.str() == trav1[2]);

    io.str("");
    pre.str("");
    post.str("");
    io.clear();
    pre.clear();
    post.clear();

    tree.remove(to_remove);

    tree.inorder(io);
    tree.preorder(pre);
    tree.postorder(post);
    assert(io.str() == trav2[0]);
    assert(pre.str() == trav2[1]);
    assert(post.str() == trav2[2]);
}

int main()
{
    vint v1 = { 88, 74, 94, 50, 86, 70, 81, 11, 19, 48 };
    vstring trav1 = {
        "[ 11 19 48 50 70 74 81 86 88 94 ]\n",
        "[ 88 74 50 11 19 48 70 86 81 94 ]\n",
        "[ 48 19 11 70 50 81 86 74 94 88 ]\n"
    };
    int to_remove = 74;
    vstring trav2 = {
        "[ 11 19 48 50 70 81 86 88 94 ]\n",
        "[ 88 81 50 11 19 48 70 86 94 ]\n",
        "[ 48 19 11 70 50 86 81 94 88 ]\n"
    };
    test(v1, trav1, to_remove, trav2);


    vint v2 = { 92, 19, 21, 86, 35, 64, 51, 44, 60, 91 };
    vstring trav3 = {
        "[ 19 21 35 44 51 60 64 86 91 92 ]\n",
        "[ 92 19 21 86 35 64 51 44 60 91 ]\n",
        "[ 44 60 51 64 35 91 86 21 19 92 ]\n"
    };
    to_remove = 35;
    vstring trav4 = {
        "[ 19 21 44 51 60 64 86 91 92 ]\n",
        "[ 92 19 21 86 64 51 44 60 91 ]\n",
        "[ 44 60 51 64 91 86 21 19 92 ]\n",
    };
    test(v2, trav3, to_remove, trav4);

    return 0;
}
