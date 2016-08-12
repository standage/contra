#ifndef CONTRA_NODE
#define CONTRA_NODE

#include <memory>

namespace contra_cpp
{

class node
{
    public:
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;
        int data;
        int height;

        node(int value)
            : left(nullptr), right(nullptr), data(value), height(-1) {}
        node(int value, int ht)
            : left(nullptr), right(nullptr), data(value), height(ht) {}
};
typedef std::unique_ptr<node> nodeptr;

} // namespace contra_cpp

#endif // define CONTRA_NODE
