/*
 *
 * This class represents the 2D grid of nodes that renders to the screen. It's methods are used
 * to modify the nodes and to draw them all to the screen. It is also where the algorithms are
 * performed, as they must have direct access to the 2D vector containing all nodes.
 *
 */

#ifndef PATHFINDING_GRID_H
#define PATHFINDING_GRID_H

#include <vector>
#include <map>

#include "Node.h"

using namespace std;

struct nodeMap {

    int shortestDistance;
    Node* previousNode;

    /**
     * Initializes nodemap entry with default node object and distance of 999
     */
    nodeMap();

    /**
     * Initializes nodemap entry with specific distance and previous node
     *
     * @param shortestDistance shortest distance from current node to origin
     * @param previousNode pointer to previous node in linked list of nodes from current node to origin
     */
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

    /**
     * Creates grid as 35x55
     */
    Grid();

    virtual ~Grid() = default;

    /**
     * Contains input validation to prevent a grid from having an even number of columns or
     * rows. Also ensures that the grid is larger than 5x5. Sets color of grid lines as well
     * as height and width which are calculated based on number of rows and columns. Prepares
     * the 2d vector of nodes and then calls the helper method createNodes() that actually
     * creates all of the nodes
     */
    void init();

    /**
     * Creates all of the nodes in the grid. Calculates all of their positions as well as their
     * node type based on position, ensuring that the start and target nodes are in the proper
     * places. It then adds each node to the 2D vector of nodes.
     */
    void createNodes();

    /**
     * @return number of rows in grid
     */
    int getNumRows() const;

    /**
     * @return number of columns in grid
     */
    int getNumColumns() const;

    /**
     * Used to toggle node between being a wall and unvisited node so that the user can draw and
     * remove walls from the grid.
     *
     * @param row row of grid
     * @param column column of grid
     * @param rDown whether or not the right mouse button is down, used to determine if nodes should
     * be changed to wall or unvisited
     */
    void toggleWallNode(int row, int column, bool rDown);

    /**
     * Used to set the type of a specific node in the grid.
     *
     * @param row row of grid
     * @param column column of grid
     * @param type NodeType to be set to
     */
    void setNodeType(int row, int column, NodeType type);

    /**
     * Used to move the grid and all other nodes in the grid to a different position on the screen
     *
     * @param deltaX change in x position value
     * @param deltaY change in y position value
     */
    void move(int deltaX, int deltaY);

    /**
     * Used to determine which node the mouse is hovering over when the mouse position overlaps with
     * the grid
     *
     * @param x x value of mouse position
     * @param y y value of mouse position
     * @param rDown whether or not the right mouse button was clicked
     */
    void detectMouse(int x, int y, bool rDown);

    /**
     * Goes through each node in the grid and determines which nodes neighbor it, then adds those nodes
     * to the vector of neighbors. Includes logic for edge casees where nodes have less than 4 neighbors.
     */
    void addNeighbors();

    /**
     * Overridden method that renders the grid to the window. It draws all of the lines
     * that outline the nodes as well as the nodes themselves.
     */
    void draw() const override;

    /**
     * Resets the grid back to its original states, with a start node, a target node, and
     * all other nodes being unvisited
     */
    void reset();

    /**
     * Calculates optimal theoretical path between any node and the target node
     *
     * @param node node in question
     * @return optimal theoretical distance between node and target
     */
    int heuristic(Node* node);

    /**
     * Performs dijkstra's algorithm by starting with the start node and determining the
     * shortest path to all neighboring nodes until it discovers the target. Technically
     * the current implementation is not actually dijkstra's algorithm as it stops when
     * it finds the target node, but I plan to change that in the near future.
     *
     * @param visited a vector of the visited nodes to return to the main function for rendering
     * @param path a vector of the path nodes to return to the main function for rendering
     */
    void dijkstras(vector<Node*>& visited, vector<Node*>& path);

    /**
     * Performs A* Search algorithm.
     *
     * @param visited a vector of the visited nodes to return to the main function for rendering
     * @param path a vector of the path nodes to return to the main function for rendering
     */
    void aStar(vector<Node*>& visited, vector<Node*>& path);

    /**
     * Performs Breadth First Search algorithm.
     *
     * @param visited a vector of the visited nodes to return to the main function for rendering
     * @param path a vector of the path nodes to return to the main function for rendering
     */
    void breadthFirst(vector<Node*>& visited, vector<Node*>& path);

    /**
     * Performs Depth First Search algorithm.
     * @param visited a vector of the visited nodes to return to the main function for rendering
     * @param path a vector of the path nodes to return to the main function for rendering
     */
    void depthFirst(vector<Node*>& visited, vector<Node*>& path);

};

#endif //PATHFINDING_GRID_H
