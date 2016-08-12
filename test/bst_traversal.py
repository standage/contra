from __future__ import print_function
from random import randint
from contra import BStree
import sys

def run(values, trav1, to_remove, trav2):
    tree = BStree()
    for i in values:
        tree.insert(i)

    trav1_test = [tree.inorder(), tree.preorder(), tree.postorder()]
    for t, test in zip(trav1, trav1_test):
        assert t == test, (t, test)

    tree.remove(to_remove)

    trav2_test = [tree.inorder(), tree.preorder(), tree.postorder()]
    for t, test in zip(trav2, trav2_test):
        assert t == test, (t, test)


def test_bst_traversal_1():
    """
    BST traversal test 1
    """
    values = [ 88, 74, 94, 50, 86, 70, 81, 11, 19, 48 ]
    trav1 = [
        '[ 11 19 48 50 70 74 81 86 88 94 ]\n',
        '[ 88 74 50 11 19 48 70 86 81 94 ]\n',
        '[ 48 19 11 70 50 81 86 74 94 88 ]\n'
    ]
    to_remove = 74
    trav2 = [
        '[ 11 19 48 50 70 81 86 88 94 ]\n',
        '[ 88 81 50 11 19 48 70 86 94 ]\n',
        '[ 48 19 11 70 50 86 81 94 88 ]\n'
    ]
    run(values, trav1, to_remove, trav2);


def test_bst_traversal_2():
    """
    BST traversal test 2
    """
    values = [ 92, 19, 21, 86, 35, 64, 51, 44, 60, 91 ]
    trav1 = [
        '[ 19 21 35 44 51 60 64 86 91 92 ]\n',
        '[ 92 19 21 86 35 64 51 44 60 91 ]\n',
        '[ 44 60 51 64 35 91 86 21 19 92 ]\n'
    ]
    to_remove = 35
    trav2 = [
        '[ 19 21 44 51 60 64 86 91 92 ]\n',
        '[ 92 19 21 86 64 51 44 60 91 ]\n',
        '[ 44 60 51 64 91 86 21 19 92 ]\n'
    ]
    run(values, trav1, to_remove, trav2);


def test_bst_rand():
    """
    BST traversal test (random)
    """
    tree = BStree()
    collisions = list()
    for _ in range(100000):
        i = randint(-10e8, 10e8)
        if tree.insert(i) == False:
            collisions.append(i)
    iot = tree.inorder()
    assert len(tree) == 100000 - (len(collisions))
    print("DEBUG", len(collisions), file=sys.stderr)

    lastvalue = None
    for value in iot.split():
        if value in ['[', ']']:
            continue
        val = int(value)
        if lastvalue is not None:
            assert lastvalue < val, (lastvalue, val)
        lastvalue = val

    for i in collisions:
        tree.remove(i)
    assert len(tree) == 100000 - (len(collisions) * 2)


def test_bst_height():
    """
    BST height test
    """
    values = [73, 50, 89, 65, 47, 84, 64, 55, 17, 32]
    heights = [0, 1, 1, 2, 2, 2, 3, 4, 3, 4]

    tree = BStree()
    for v in values:
        tree.insert(v)

    for v, h in zip(values, heights):
        assert tree.height(v) == h, (v, tree.height(v), h)
