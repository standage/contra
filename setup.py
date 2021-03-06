#!/usr/bin/env python
#
# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

from setuptools import setup, Extension
import versioneer
import glob

headers = list(glob.glob('inc/*.hpp'))
sources = list(glob.glob('src/*.cpp'))
cythons = ['contra.pyx']

contra = Extension(
    'contra',
    sources=cythons + sources,
    include_dirs=['inc/', 'third-party/cereal-1.2.2/include/'],
    language='c++',
    extra_compile_args=['--std=c++11', '-Wno-unused-function'],
    extra_link_args=['--std=c++11'],
)

setup(
    name='contra',
    description='High-performance containers with a Python interface',
    url='http://github.com/standage/contra',
    author='Daniel Standage',
    author_email='daniel.standage@gmail.com',
    license='MIT',
    ext_modules=[contra],
    install_requires=['setuptools>=18.0', 'cython'],
    tests_require=['pytest'],
    version=versioneer.get_version(),
    cmdclass=versioneer.get_cmdclass(),
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Topic :: Scientific/Engineering :: Bio-Informatics'
    ],
)
