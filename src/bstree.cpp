#include "bstree.hpp"
#include "node.hpp"

using namespace contra_cpp;

bool bstree::insert(int value)
{
    return insert(_root, value, -1);
}

bool bstree::search(int value)
{
    return search(_root, value);
}

void bstree::remove(int value)
{
    _root = remove(_root, value);
}

unsigned int bstree::size()
{
    return _count;
}

int bstree::height(int value)
{
    return height(_root, value);
}

void bstree::inorder(std::ostream& stream)
{
    stream << "[";
    inorder(_root, stream);
    stream << " ]" << std::endl;
}

void bstree::preorder(std::ostream& stream)
{
    stream << "[";
    preorder(_root, stream);
    stream << " ]" << std::endl;
}

void bstree::postorder(std::ostream& stream)
{
    stream << "[";
    postorder(_root, stream);
    stream << " ]" << std::endl;
}

bool bstree::insert(nodeptr& root, int value, int height)
{
    if (!root) {
        root = nodeptr(new node(value, height + 1));
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

bool bstree::search(nodeptr& root, int value)
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

nodeptr bstree::remove(nodeptr& root, int value, bool decr)
{
    if (!root) {
        return std::move(root);
    }
    else if (value > root->data) {
        root->right = remove(root->right, value, decr);
    }
    else if (value < root->data) {
        root->left = remove(root->left, value, decr);
    }
    else {
        nodeptr temp = std::move(root);
        if (temp->left == temp->right) {
            _count--;
            return nodeptr();
        }
        if (!temp->left) {
            _count--;
            if(decr)
                decr_height(temp->right);
            return std::move(temp->right);
        }
        if (!temp->right) {
            _count--;
            if(decr)
                decr_height(temp->left);
            return std::move(temp->left);
        }

        int height = temp->height;
        nodeptr minright = minimum(temp->right);
        minright->height = height;
        minright->left = std::move(temp->left);
        minright->right = remove(temp, value, false);
        return minright;
    }
    return std::move(root);
}

nodeptr bstree::minimum(nodeptr& root)
{
    if (!root || !root->left) {
        return std::move(root);
    }
    return minimum(root->left);
}

int bstree::height(nodeptr& root, int value)
{
    if (!root) {
        return -1;
    }
    else if (value == root->data) {
        return root->height;
    }
    else if (value > root->data) {
        return height(root->right, value);
    }
    else {
        return height(root->left, value);
    }
}

void bstree::decr_height(nodeptr& root)
{
    if (!root) {
        return;
    }
    root->height -= 1;
    decr_height(root->left);
    decr_height(root->right);
}

void bstree::inorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        inorder(root->left, stream);
        stream << " " << root->data;
        inorder(root->right, stream);
    }
}

void bstree::preorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        stream << " " << root->data;
        preorder(root->left, stream);
        preorder(root->right, stream);
    }
}

void bstree::postorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        postorder(root->left, stream);
        postorder(root->right, stream);
        stream << " " << root->data;
    }
}
