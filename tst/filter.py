# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from __future__ import print_function
from contra import BloomFilter, CountFilter, BigCountFilter
import sys


def test_filter_basic():
    """
    Test basic essentials: contruct, add, get
    """
    bf = BloomFilter(90, 2)
    bf.add(101)
    assert bf.get(101) is True
    assert bf.get(100) is False

    cf = CountFilter(120, 2)
    cf.add(101)
    assert cf.get(101) == 1
    assert cf.get(100) == 0
    for i in range(100):
        cf.add(101)
    assert cf.get(101) == 101

    bcf = BigCountFilter(200, 2)
    bcf.add(101)
    assert bcf.get(101) == 1
    assert bcf.get(100) == 0
    for i in range(1024):
        bcf.add(101)
    assert bcf.get(101) == 1025

def test_filter_size():
    bf = BloomFilter(90, 2)
    # 90 bytes / 2 hash functions * 8 buckets per byte = 360 buckets per table
    # The closest prime numbers to 360 are 359 and 353
    assert len(bf) == 359 + 353
    bf.add(101)
    assert len(bf) == 359 + 353

    # 2000 bytes / 2 hash functions * 1 bucket per byte = 1000 buckets per table
    cf = CountFilter(2000, 2)
    assert len(cf) == 997 + 991
    cf.add(101)
    assert len(cf) == 997 + 991

    # 16000 bytes / 4 hash functions / 4 bytes per bucket per byte = 1000 buckets per table
    bcf = BigCountFilter(16000)
    assert len(bcf) == 997 + 991 + 983 + 977
    bcf.add(101)
    assert len(bcf) == 997 + 991 + 983 + 977
