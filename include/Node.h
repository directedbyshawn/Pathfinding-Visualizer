#ifndef PATHFINDING_NODE_H
#define PATHFINDING_NODE_H

#include "Entity.h"
#include <vector>

class Node : public Entity {

private:

    int row;
    int column;
    int id;
    NodeType type;
    std::vector<Node*> neighbors;

public:

    Node();
    Node(int row, int column);
    Node(int row, int column, NodeType type);
    Node(Node* copy);

    virtual ~Node() = default;

    int getRow() const;
    void setRow(int row);
    int getColumn() const;
    void setColumn(int column);
    int getId() const;
    void setId(int id);
    void setPosition(int row, int column);
    void setNodeType(NodeType type);
    NodeType getNodeType() const;
    void setNodeColor();
    int getNumNeighbors() const;
    std::vector<Node*> getNeighbors() const;
    void addNeighbor(Node* newNeighbor);
    void draw() const override;

};

#endif //PATHFINDING_NODE_H
