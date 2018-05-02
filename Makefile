# -----------------------------------------------------------------------------
# Copyright (c) 2016   Daniel Standage <daniel.standage@gmail.com>
#
# This file is part of contra (http://github.com/standage/contra) and is
# licensed under the MIT license: see LICENSE.txt.
# -----------------------------------------------------------------------------

# Install configs
PREFIX=/usr/local

# Compilation configs
CXXFLAGS=-Wall -O3 --std=c++11 -Iinc/ -fPIC

# Source/header files
HEADERS=inc/node.hpp inc/bstree.hpp inc/filter.hpp


# Determine package version from git commits/tags
ifneq ($(PACKAGE_VERSION),)
LIB_VERSION = $(PACKAGE_VERSION)
else
LIB_VERSION = $(shell python setup.py version \
                    | grep Version \
                    | cut -f 2 -d ' ' \
                    | cut -f 1 -d + \
                    && rm -rf __pycache__)
endif

# Dynamic library config
ifeq ($(shell uname), Darwin)
SHARED_EXT   = dylib
SONAME       = libcontra.$(SHARED_EXT).$(LIB_VERSION)
SONAME_FLAGS = -install_name $(PREFIX)/lib/$(SONAME) \
               -compatibility_version $(LIB_VERSION) \
               -current_version $(LIB_VERSION)
else
SHARED_EXT   = so
SONAME       = libcontra.$(SHARED_EXT).$(LIB_VERSION)
SONAME_FLAGS = -Wl,-soname=$(SONAME)
endif


# Python targets

test: install
	@ py.test -v tst/*.py

style:
	@ pep8 tst/*.py

install:
	@ pip install -e .

devenv:
	@ pip install --upgrade cython pep8 pytest

tree:
	@ tree -I 'build|__pycache__|contra.cpp'

clean:
	@ rm -rf build/ *.egg-info/ dist/ src/*.o *.$(SHARED_EXT)* __pycache__/ \
	  contra.cpp aux/contra.pc test/__pycache__/ libtest.txt

build:
	@ python setup.py sdist build

pypi:
	@ python setup.py sdist upload



# C++ library targets

lib: aux/$(SONAME) aux/contra.pc

src/%.o: src/%.cpp
	@ $(CXX) $(CXXFLAGS) -c -o $@ $^

aux/$(SONAME): src/bstree.o src/filter.o
	@ $(CXX) $(CXXFLAGS) -shared -o $@ $^
	@ ln -sf $(SONAME) aux/libcontra.$(SHARED_EXT)


aux/contra.pc: aux/contra.pc.in
	@ sed -e 's,@prefix@,$(PREFIX),' -e 's,@VERSION@,$(VERSION),' $< > $@

libinstall: aux/$(SONAME) aux/contra.pc $(HEADERS)
	mkdir -p $(PREFIX)/lib/ $(PREFIX)/lib/pkgconfig/ $(PREFIX)/include/contra/
	cp $(HEADERS) $(PREFIX)/include/contra/
	cp aux/contra.pc $(PREFIX)/lib/pkgconfig/
	cp aux/libcontra* $(PREFIX)/lib/

libuninstall:
	rm -rf $(PREFIX)/include/contra/ $(PREFIX)/lib/libcontra.* \
           $(PREFIX)/lib/pkgconfig/contra.pc

libtest:
	cd aux && make
	aux/example > libtest.txt
	shasum -c aux/libtest-out-check.shasum
