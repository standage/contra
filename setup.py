#!/usr/bin/env python
#
# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/genhub) and is
# licensed under the BSD 3-clause license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from setuptools import setup, Extension

contra = Extension(
    'contra',
    sources=['contra.pyx', 'src/bstree.cpp'],
    include_dirs=['inc/'],
    language='c++',
    extra_compile_args=['--std=c++11', '-Wno-unused-function'],
    extra_link_args=['--std=c++11'],
)

setup(
    name='contra',
    description='high-performance containers with a Python interface',
    ext_modules=[contra],
    install_requires=['cython', 'pep8', 'pytest'],
)
