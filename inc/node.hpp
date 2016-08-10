#ifndef DSS_NODE
#define DSS_NODE

#include <memory>

namespace dss
{

class Node
{
    public:
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int data;
        int height() {
            return _height;
        }

        Node(int value)
            : left(nullptr), right(nullptr), data(value), _height(-1) {}
        Node(int value, int ht)
            : left(nullptr), right(nullptr), data(value), _height(ht) {}

    protected:
        int _height;
};
typedef std::unique_ptr<Node> nodeptr;

} // namespace dss

#endif // define DSS_NODE
