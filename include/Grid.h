#ifndef PATHFINDING_GRID_H
#define PATHFINDING_GRID_H

#include <vector>
#include <map>

#include "Node.h"

using namespace std;

struct nodeMap {

    int shortestDistance;
    Node* previousNode;

    nodeMap();
    nodeMap(int shortestDistance, Node* previousNode);

};

class Grid : public Entity {

private:

    vector<vector<Node>> nodes;
    int numRows;
    int numColumns;
    Node* startNode;
    Node* targetNode;

public:

    Grid();
    Grid(int numRows, int numColumns);

    void init();

    virtual ~Grid() = default;

    int getNumRows() const;
    void setNumRows(int numRows);
    int getNumColumns() const;
    void setNumColumns(int numColumns);
    void toggleWallNode(int row, int column, bool rDown);
    void setNodeType(int row, int column, NodeType type);
    void createNodes();
    void move(int deltaX, int deltaY);
    void detectMouse(int x, int y, bool rDown);
    void addNeighbors();
    void drawNeighbors();
    void drawNode(int column, int row);
    void draw() const override;

    void reset();
    void printNodeMap(vector<Node*>& unvisited, map<Node*, nodeMap>& pathMap);
    void dijkstras(vector<Node*>& visited, vector<Node*>& path);
    void aStar();
    void breadthFirst();
    void depthFirst();

};

#endif //PATHFINDING_GRID_H
