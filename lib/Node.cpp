#include "Node.h"

Node::Node() : Entity(), row(0), column(0), id(-1) {
    setNodeType(UNVISITED);
}

Node::Node(int row, int column) : Entity(), row(row), column(column), id(-1) {
    setNodeType(UNVISITED);
}

Node::Node(int row, int column, NodeType type) : Entity(), id(-1) {
    this->row = row;
    this->column = column;
    this->type = type;
    setNodeType(type);
}

Node::Node(Node* copy) {
    this->row = copy->getRow();
    this->column = copy->getColumn();
    this->id = copy->getId();
    this->type = copy->getNodeType();
    for (Node* neighbor : copy->getNeighbors()) {
        this->neighbors.push_back(neighbor);
    }
}

int Node::getRow() const {
    return row;
}

void Node::setRow(int row) {
    this->row = row;
}

int Node::getColumn() const {
    return column;
}

void Node::setColumn(int column) {
    this->column = column;
}

void Node::setPosition(int row, int column) {
    this->row = row;
    this->column = column;
}

int Node::getId() const {
    return id;
}

void Node::setId(int id) {
    this->id = id;
}

void Node::setNodeType(NodeType type) {
    this->type = type;
    setNodeColor();
}

NodeType Node::getNodeType() const {
    return type;
}

void Node::setNodeColor() {
    if (getNodeType() == UNVISITED) {
        setColor(148.0/255, 148.0/255.0, 148.0/255.0);
    }
    else if (getNodeType() == VISITED) {
        setColor(128.0/255.0, 111.0/255.0, 233.0/255.0);
    }
    else if (getNodeType() == START) {
        setColor(39.0/255.0, 229.0/255.0, 255.0/255.0);
    }
    else if (getNodeType() == TARGET) {
        setColor(255.0/255.0, 0.0, 0.0);
    }
    else if (getNodeType() == WALL) {
        setColor(0.0, 0.0, 0.0);
    }
    else if (getNodeType() == PATH) {
        setColor(251.0/255.0, 255.0/255.0, 39.0/255.0);
    }
    else {
        setColor(0.0, 0.0, 0.0);
    }
}

int Node::getNumNeighbors() const {
    return neighbors.size();
}

std::vector<Node*> Node::getNeighbors() const {
    return neighbors;
}

void Node::addNeighbor(Node* newNeighbor) {
    if (neighbors.size() < 4) {
        neighbors.push_back(newNeighbor);
    }
}

void Node::draw() const {
    glBegin(GL_QUADS);
    glColor3f(getRed(), getGreen(), getBlue());
    glVertex2f(getRightX(), getTopY());
    glVertex2f(getLeftX(), getTopY());
    glVertex2f(getLeftX(), getBottomY());
    glVertex2f(getRightX(), getBottomY());
    glEnd();
}
