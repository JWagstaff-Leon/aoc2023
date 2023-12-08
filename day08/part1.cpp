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

    std::shared_ptr<Node> startNode = findNodeWithNameIn("AAA", nodes);
    std::shared_ptr<Node> currentNode = startNode;

    uint64_t answer = 0;
    for(int i = 0; currentNode->getName() != "ZZZ"; i = (i + 1) % directions.length(), answer++)
    {
        switch(directions[i])
        {
            case 'L':
                currentNode = currentNode->getLeft();
                break;

            case 'R':
                currentNode = currentNode->getRight();
                break;
            
            default:
                std::cerr << "Something went wrong; input character was \'" << directions[i] << "\' (" << (int)directions[i] << ")\n";
                assert(false);
        }
    }

    std::cout << "Answer: " << answer << "\n";
    return 0;
}