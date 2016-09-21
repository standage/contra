# Contra

[![Contra build status][travisbadge]](https://travis-ci.org/standage/contra)
[![MIT licensed][mit]](https://github.com/standage/contra/blob/master/LICENSE.txt)

Contra provides a variety of high-performance dynamic containers.
The core is implemented in C++, but is accessed primarily through Python.

This is currently a personal research project intended to hone my skills in C++ programming, C++/Python integration, and cross-platform DevOps.
Maybe one day it will be useful enough for people to actually use!

## Python API

```python
>>> from contra import BStree
>>> tree = BStree()
>>> for value in [2, 32, 95, 71, -36, -35, -27, -19, 9, -82]:
...     success = tree.insert(value)
...
>>> len(tree)
10
>>> tree.search(-35)
True
>>> tree.search(1)
False
>>>
```

`BStree` uses the default integer type (a 32-bit signed integer).
You can use `BStreeLarge` to support working with large (64-bit unsigned) integers, or `BStreeSmall` to use small (8-bit unsigned) integers (if you are working with small numbers and optimizing for memory consumption).

## C++ API

Only the Python API is under semantic versioning: no guarantees at the C++ level (yet).

```c++
#include <iostream>
#include <vector>
#include "bstree.hpp"

using namespace contra_cpp;

int main()
{
    bstree<int> tree;
    std::vector<int> values = {2, 32, 95, 71, -36, -35, -27, -19, 9, -82};
    for (auto v : values) {
        tree.insert(v);
    }
    tree.inorder();
    return 0;
}
```

To compile and run...

```
$ pkg-config contra --cflags-only-I
/usr/local/include/contra
$ g++ -Wall --std=c++11 /usr/local/include/contra -o example example.cpp -lcontra
$ ./example
[ -82 -36 -35 -27 -19 2 9 32 71 95 ]
$
```
