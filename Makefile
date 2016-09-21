PREFIX=/usr/local
CXXFLAGS=-Wall -O3 --std=c++11 -Iinc/

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


test: install
	@ rm -f .coverage
	@ py.test -v test/*.py

style:
	@ pep8 test/*.py

install:
	@ python setup.py install

depend:
	@ pip install --upgrade cython pep8 pytest coverage

tree:
	@ tree -I 'build|__pycache__|contra.cpp'

clean:
	@ rm -rf .coverage build/ *.egg-info/ dist/ src/*.o *.$(SHARED_EXT)*

lib: $(SONAME)

src/%.o: src/%.cpp
	@ $(CXX) $(CXXFLAGS) -c -o $@ $^

$(SONAME): src/bstree.o
	@ $(CXX) $(CXXFLAGS) -shared -o $@ $^
	@ ln -s $(SONAME) libcontra.$(SHARED_EXT)
