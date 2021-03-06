# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from __future__ import print_function
from random import randint
from contra import BStree, BStreeLarge, BStreeSmall
import pytest
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
    values = [88, 74, 94, 50, 86, 70, 81, 11, 19, 48]
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
    run(values, trav1, to_remove, trav2)


def test_bst_traversal_2():
    """
    BST traversal test 2
    """
    values = [92, 19, 21, 86, 35, 64, 51, 44, 60, 91]
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
    run(values, trav1, to_remove, trav2)


def test_bst_rand():
    """
    BST traversal test (random)
    """
    tree = BStree()
    collisions = list()
    for _ in range(100000):
        i = randint(-10e8, 10e8)
        if tree.insert(i) is False:
            collisions.append(i)
    iot = tree.inorder()
    assert len(tree) == 100000 - (len(collisions))

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


def test_bst_height_1():
    """
    BST height test 1
    """
    values = [73, 50, 89, 65, 47, 84, 64, 55, 17, 32]
    heights = [0, 1, 1, 2, 2, 2, 3, 4, 3, 4]

    tree = BStree()
    for v in values:
        tree.insert(v)

    for v, h in zip(values, heights):
        assert tree.height(v) == h, (v, tree.height(v), h)

    tree.remove(50)
    for v, h in zip([73, 55, 65, 64, 47, 89], [0, 1, 2, 3, 2, 1]):
        assert tree.height(v) == h, (v, tree.height(v), h)

    tree.remove(47)
    for v, h in zip([73, 55, 17, 32, 65], [0, 1, 2, 3, 2]):
        assert tree.height(v) == h, (v, tree.height(v), h)


def test_bst_height_2():
    """
    BST height test 2
    """
    values = [96, 64, 49, 62, -11, 81, -95, -33, -80, 14, -74, 56, 79, 17,
              -75, 83, -72, 23, -42, -55, 100, -22]
    heights = [0, 1, 2, 3, 3, 2, 4, 5, 6, 4, 7, 4, 3, 5, 8, 3, 8, 6, 9, 10, 1,
               6]

    tree = BStree()
    for v in values:
        tree.insert(v)

    for v, h in zip(values, heights):
        assert tree.height(v) == h, (v, tree.height(v), h)

    pre = ('[ 96 64 49 -11 -95 -33 -80 -74 -75 -72 -42 -55 -22 14 17 23 62 56 '
           '81 79 83 100 ]\n')
    pretest = tree.preorder()
    assert pretest == pre, (pretest, pre)


def test_bst_large():
    """
    BST large numbers
    """

    tree = BStreeLarge()
    values = [3e9, 3.7e9, 2.1e7, 4.4e8, 4.4e9, 1, 3.6e9, 5e14]
    for v in values:
        tree.insert(v)
    inorder = ('[ 1 21000000 440000000 3000000000 3600000000 3700000000 '
               '4400000000 500000000000000 ]\n')
    inordertest = tree.inorder()
    assert inordertest == inorder, (inordertest, inorder)


def test_bst_small():
    """
    BST small numbers
    """

    tree = BStreeSmall()
    with pytest.raises(OverflowError):
        for v in [254, 255, 256, 257]:
            tree.insert(v)

    tree = BStreeSmall()
    values = [128, 64, 196, 4, 16]
    for v in values:
        tree.insert(v)
    inorder = '[ 4 16 64 128 196 ]\n'
    inordertest = tree.inorder()
    assert inordertest == inorder, (inordertest, inorder)
