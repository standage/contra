# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from __future__ import print_function
from contra import BloomFilter, CountFilter, BigCountFilter
import random
import sys
from tempfile import NamedTemporaryFile


def test_filter_basic():
    """
    Test basic essentials: contruct, add, get
    """
    bf = BloomFilter(90, 2)
    bf.insert(101)
    assert bf.query(101) is True
    assert bf.query(100) is False

    cf = CountFilter(120, 2)
    cf.insert(101)
    assert cf.query(101) == 1
    assert cf.query(100) == 0
    for i in range(100):
        cf.insert(101)
    assert cf.query(101) == 101

    bcf = BigCountFilter(200, 2)
    bcf.insert(101)
    assert bcf.query(101) == 1
    assert bcf.query(100) == 0
    for i in range(1024):
        bcf.insert(101)
    assert bcf.query(101) == 1025


def test_filter_size():
    bf = BloomFilter(90, 2)
    # 90 bytes / 2 hash functions * 8 buckets per byte = 360 buckets per table
    # The closest prime numbers to 360 are 359 and 353
    assert len(bf) == 359 + 353
    bf.insert(101)
    assert len(bf) == 359 + 353

    # 2000 bytes / 2 hash functions * 1 bucket per byte = 1000 buckets per table
    cf = CountFilter(2000, 2)
    assert len(cf) == 997 + 991
    cf.insert(101)
    assert len(cf) == 997 + 991

    # 16000 bytes / 4 hash functions / 4 bytes per bucket per byte = 1000 buckets per table
    bcf = BigCountFilter(16000)
    assert len(bcf) == 997 + 991 + 983 + 977
    bcf.insert(101)
    assert len(bcf) == 997 + 991 + 983 + 977


def test_filter_save_load():
    # Populate a count filter with 100 random elements between 1 and 100,000,
    # each element with a random abundance between 1 and 10.
    counts = CountFilter(5e4, 4)
    testcounts = dict()
    for _ in range(100):
        element = random.randint(0, 1e5)
        abund = random.randint(1, 10)
        testcounts[element] = abund
        for _ in range(abund):
            counts.insert(element)

    # Save the filter to disk, load it again, and check to make sure everything
    # matches.
    loadcounts = CountFilter(1, 1)
    with NamedTemporaryFile(suffix='.kct') as diskfile:
        counts.save(diskfile.name)
        loadcounts.load(diskfile.name)
    for e in range(int(1e5)):
        if e in testcounts:
            assert loadcounts.query(e) == testcounts[e]
        else:
            assert loadcounts.query(e) == 0
