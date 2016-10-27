# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from __future__ import print_function
from contra import BloomFilter, CountFilter, BigCountFilter
import sys


def test_basic():
    """
    Test basic essentials: contruct, add, get
    """
    bf = BloomFilter([47, 43])
    bf.add(101)
    assert bf.get(101) is True
    assert bf.get(100) is False

    cf = CountFilter([57, 53])
    cf.add(101)
    assert cf.get(101) == 1
    assert cf.get(100) == 0
    for i in range(100):
        cf.add(101)
    assert cf.get(101) == 101

    bcf = BigCountFilter([97, 91])
    bcf.add(101)
    assert bcf.get(101) == 1
    assert bcf.get(100) == 0
    for i in range(1024):
        bcf.add(101)
    assert bcf.get(101) == 1025
