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
	@ rm -f .coverage build/ *.egg-info/ dist/
