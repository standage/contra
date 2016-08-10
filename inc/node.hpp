#ifndef DSS_NODE
#define DSS_NODE

#include <memory>

namespace dss
{

struct Node
{
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    int data;

    Node(int value) : left(nullptr), right(nullptr), data(value) {}
};
typedef std::unique_ptr<Node> nodeptr;

} // namespace dss

#endif // define DSS_NODE
