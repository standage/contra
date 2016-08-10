#include "bstree.hpp"
#include "node.hpp"

using namespace dss;

bool BStree::insert(int value)
{
    return insert(_root, value, -1);
}

bool BStree::search(int value)
{
    return search(_root, value);
}

void BStree::remove(int value)
{
    _root = remove(_root, value);
}

unsigned int BStree::size()
{
    return _count;
}

void BStree::inorder(std::ostream& stream)
{
    stream << "[";
    inorder(_root, stream);
    stream << " ]" << std::endl;
}

void BStree::preorder(std::ostream& stream)
{
    stream << "[";
    preorder(_root, stream);
    stream << " ]" << std::endl;
}

void BStree::postorder(std::ostream& stream)
{
    stream << "[";
    postorder(_root, stream);
    stream << " ]" << std::endl;
}

bool BStree::insert(nodeptr& root, int value, int height)
{
    if (!root) {
        root = nodeptr(new Node(value, height + 1));
        _count++;
        return true;
    }
    else if (value > root->data) {
        return insert(root->right, value, height + 1);
    }
    else if (value < root->data) {
        return insert(root->left, value, height + 1);
    }
    return false;
}

bool BStree::search(nodeptr& root, int value)
{
    if (!root) {
        return false;
    }
    else if (value == root->data) {
        return true;
    }
    else if (value > root->data) {
        return search(root->right, value);
    }
    else {
        return search(root->left, value);
    }

}

nodeptr BStree::remove(nodeptr& root, int value)
{
    if (!root) {
        return std::move(root);
    }
    else if (value > root->data) {
        root->right = remove(root->right, value);
    }
    else if (value < root->data) {
        root->left = remove(root->left, value);
    }
    else {
        nodeptr temp = std::move(root);
        if (temp->left == temp->right) {
            _count--;
            return nodeptr();
        }
        if (!temp->left) {
            _count--;
            return std::move(temp->right);
        }
        if (!temp->right) {
            _count--;
            return std::move(temp->left);
        }

        nodeptr minright = minimum(temp->right);
        minright->left = std::move(temp->left);
        minright->right = remove(temp, value);
        return minright;
    }
    return std::move(root);
}

nodeptr BStree::minimum(nodeptr& root)
{
    if (!root || !root->left) {
        return std::move(root);
    }
    return minimum(root->left);
}

void BStree::inorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        inorder(root->left, stream);
        stream << " " << root->data;
        inorder(root->right, stream);
    }
}

void BStree::preorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        stream << " " << root->data;
        preorder(root->left, stream);
        preorder(root->right, stream);
    }
}

void BStree::postorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        postorder(root->left, stream);
        postorder(root->right, stream);
        stream << " " << root->data;
    }
}
