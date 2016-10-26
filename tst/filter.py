# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from __future__ import print_function
from contra import BloomFilter, CountFilter, BigCountFilter
import sys


def test_construct():
    """
    Constructors
    """
    bf = BloomFilter([47, 43])
    cf = CountFilter([57, 53])
    bcf = BigCountFilter([97, 91])
