#include "Node.h"

Node::Node(std::string name)
: name_(name) { /* Intentionally empty */ };



std::string Node::getName() const
{
    return name_;
};



void Node::setLeft(std::shared_ptr<Node> left)
{
    left_ = left;
};



void Node::setRight(std::shared_ptr<Node> right)
{
    right_ = right;
};



std::shared_ptr<Node> Node::getLeft() const
{
    return left_;
};



std::shared_ptr<Node> Node::getRight() const
{
    return right_;
};