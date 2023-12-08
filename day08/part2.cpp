#include <algorithm>
#include <assert.h>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "helpers.h"
#include "Node.h"

bool nodeNameMatches(std::shared_ptr<Node> node, std::string name)
{
    return node->getName() == name;
};



std::shared_ptr<Node> findNodeWithNameIn(std::string name, std::vector<std::shared_ptr<Node>> nodes)
{
    auto found = std::find_if(
        nodes.begin(),
        nodes.end(),
        std::bind(nodeNameMatches, std::placeholders::_1, name)
    );
    if(found == nodes.end())
    {
        std::shared_ptr<Node> emptyPtr;
        return emptyPtr;
    }
    return *found;
};



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input filename>" << std::endl;
        return 0;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail())
    {
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 0;
    }

    std::string directions;
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::pair<std::shared_ptr<Node>, std::pair<std::string, std::string>>> nodeConnections;
    std::getline(fin, directions);

    std::string currentLine;
    while(!fin.eof())
    {
        std::getline(fin, currentLine);
        if(currentLine.length() == 0)
            continue;

        std::vector<std::string> nameAndNodes = helpers::splitString(currentLine, {" = "});
        nameAndNodes[1] = nameAndNodes[1].substr(1, nameAndNodes[1].length() - 2); // remove parenthesis from connections
        std::vector<std::string> connections = helpers::splitString(nameAndNodes[1], {", "});
        std::shared_ptr<Node> newNode = std::make_shared<Node>(nameAndNodes[0]);
        nodes.push_back(newNode);
        nodeConnections.push_back(std::make_pair(newNode, std::make_pair(connections[0], connections[1])));
    }
    fin.close();

    for(auto connection : nodeConnections)
    {
        std::shared_ptr<Node> node = connection.first;

        auto leftNode = findNodeWithNameIn(connection.second.first, nodes);
        auto rightNode = findNodeWithNameIn(connection.second.second, nodes);

        node->setLeft(leftNode);
        node->setRight(rightNode);
    }

    std::vector<std::shared_ptr<Node>> startNodes;
    std::vector<std::shared_ptr<Node>> currentNodes;
    for(auto node : nodes)
    {
        if(node->getName().substr(node->getName().length() - 1, 1) == "A")
        {
            startNodes.push_back(node);
            currentNodes.push_back(node);
        }
    }
        
    std::vector<uint64_t> steps;
    for(int currentIndex = 0; currentIndex < currentNodes.size(); currentIndex++)
    {
        uint64_t stepCount = 0;
        bool zEnding = false;
        for(int directionIndex = 0; !zEnding; directionIndex = (directionIndex + 1) % directions.length(), stepCount++)
        {
            switch(directions[directionIndex])
            {
                case 'L':
                    currentNodes[currentIndex] = currentNodes[currentIndex]->getLeft();
                    break;

                case 'R':
                    currentNodes[currentIndex] = currentNodes[currentIndex]->getRight();
                    break;
                
                default:
                    std::cerr << "Something went wrong; input character was \'" << directions[directionIndex] << "\' (" << (int)directions[directionIndex] << ")\n";
                    assert(false);
            }

            std::string currentName = currentNodes[currentIndex]->getName();
            zEnding = currentName.substr(currentName.length() - 1, 1) == "Z";
        }
        steps.push_back(stepCount);
    }

    uint64_t answer = 0;
    bool answerFound = false;
    for(int i = 1; !answerFound; i++)
    {
        answer = steps[0] * i;
        answerFound = true;
        for(int j = 1; j < steps.size(); j++)
            answerFound = answerFound && answer % steps[j] == 0;
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
};