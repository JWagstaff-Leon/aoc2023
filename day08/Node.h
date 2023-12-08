#pragma once

#include <memory>
#include <string>

class Node
{
    public:
        Node(std::string name);
        std::string getName() const;

        void setLeft(std::shared_ptr<Node> left);
        void setRight(std::shared_ptr<Node> right);

        std::shared_ptr<Node> getLeft() const;
        std::shared_ptr<Node> getRight() const;
    
    private:
        std::string name_;
        std::shared_ptr<Node> left_, right_;
};