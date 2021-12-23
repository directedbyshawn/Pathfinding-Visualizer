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

    /**
     * Initializes node at position (0, 0) with an id of -1 as unvisited
     */
    Node();

    /**
     * Initializes node at custom position with an id of -1 as unvisited
     *
     * @param row row of node relative to grid
     * @param column column of node relative to grid
     */
    Node(int row, int column);

    /**
     * Initializes node with id of -1 with custom row, column, and type
     *
     * @param row row of node relative to grid
     * @param column column of node relative to grid
     * @param type node type
     */
    Node(int row, int column, NodeType type);

    /**
     * Copy constructor
     *
     * @param copy copy node
     */
    explicit Node(Node* copy);

    /**
     * Default destructor
     */
    virtual ~Node() = default;

    /**
     * Row of node within grid
     *
     * @return row of node within grid
     */
    int getRow() const;

    /**
     * Row of node within grid
     *
     * @param row of node within grid
     */
    void setRow(int row);

    /**
     * Column of node within grid
     *
     * @return column of node within grid
     */
    int getColumn() const;

    /**
     * Column of node within grid
     *
     * @param column of node within grid
     */
    void setColumn(int column);

    /**
     * Id of node
     *
     * @return id of node
     */
    int getId() const;

    /**
     * Id of node
     *
     * @param id id of node
     */
    void setId(int id);

    /**
     * Sets position of node within grid
     *
     * @param row row of node
     * @param column column of node
     */
    void setPosition(int row, int column);

    /**
     * Sets node type
     *
     * @param type node type
     */
    void setNodeType(NodeType type);

    /**
     * Gets node type
     *
     * @return node type
     */
    NodeType getNodeType() const;

    /**
     * Set node color
     */
    void setNodeColor();

    /**
     * Get number of neighbors node has
     *
     * @return number of neighbors
     */
    int getNumNeighbors() const;

    /**
     * Get vector of neighbors
     *
     * @return vector of pointers to neighbors
     */
    std::vector<Node*> getNeighbors() const;

    /**
     * Add new neighbor
     *
     * @param newNeighbor new neighbor node
     */
    void addNeighbor(Node* newNeighbor);

    /**
     * Draw node to display
     */
    void draw() const override;

};

#endif //PATHFINDING_NODE_H
