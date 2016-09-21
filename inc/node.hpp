#ifndef CONTRA_NODE
#define CONTRA_NODE

#include <memory>

namespace contra_cpp
{

template<typename Data>
class node
{
    public:
        std::unique_ptr<node<Data>> left;
        std::unique_ptr<node<Data>> right;
        Data data;
        int height;

        node(int value)
            : left(nullptr), right(nullptr), data(value), height(-1) {}
        node(int value, int ht)
            : left(nullptr), right(nullptr), data(value), height(ht) {}
};

} // namespace contra_cpp

#endif // define CONTRA_NODE
