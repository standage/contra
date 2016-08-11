#!/usr/bin/env python
#
# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/genhub) and is
# licensed under the BSD 3-clause license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    name='contra',
    description='high-performance containers with a Python interface',
    ext_modules=cythonize(Extension(
        'contra',
        sources=['aux/contra.pyx', 'src/bstree.cpp'],
        include_dirs=['inc/'],
        language='c++',
        extra_compile_args=['--std=c++11'],
        extra_link_args=['--std=c++11']
    )),
)
