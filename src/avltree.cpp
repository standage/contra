#include "avltree.hpp"

using namespace dss_avl_tree;
typedef dss_avl_tree::AVLtree::nodeptr nodeptr;

void AVLtree::insert(int value)
{
    insert(_root, value);
}

bool AVLtree::search(int value)
{
    return search(_root, value);
}

void AVLtree::remove(int value)
{
    _root = remove(_root, value);
}

void AVLtree::inorder(std::ostream& stream)
{
    stream << "[";
    inorder(_root, stream);
    stream << " ]" << std::endl;
}

void AVLtree::preorder(std::ostream& stream)
{
    stream << "[";
    preorder(_root, stream);
    stream << " ]" << std::endl;
}

void AVLtree::postorder(std::ostream& stream)
{
    stream << "[";
    postorder(_root, stream);
    stream << " ]" << std::endl;
}

void AVLtree::insert(nodeptr& root, int value)
{
    if (!root) {
        root = nodeptr(new AVLnode(value));
    }
    else if (value > root->data) {
        insert(root->right, value);
    }
    else {
        insert(root->left, value);
    }
}

bool AVLtree::search(nodeptr& root, int value)
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

nodeptr AVLtree::remove(nodeptr& root, int value)
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
            return nodeptr();
        }
        if (!temp->left) {
            return std::move(temp->right);
        }
        if (!temp->right) {
            return std::move(temp->left);
        }

        nodeptr minright = minimum(temp->right);
        minright->left = std::move(temp->left);
        minright->right = remove(temp, value);
        return minright;
    }
    return std::move(root);
}

nodeptr AVLtree::minimum(nodeptr& root)
{
    if (!root || !root->left) {
        return std::move(root);
    }
    return minimum(root->left);
}

void AVLtree::inorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        inorder(root->left, stream);
        stream << " " << root->data;
        inorder(root->right, stream);
    }
}

void AVLtree::preorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        stream << " " << root->data;
        preorder(root->left, stream);
        preorder(root->right, stream);
    }
}

void AVLtree::postorder(nodeptr& root, std::ostream& stream)
{
    if(root) {
        postorder(root->left, stream);
        postorder(root->right, stream);
        stream << " " << root->data;
    }
}