#include "Grid.h"
#include <math.h>
#include <map>

nodeMap::nodeMap() : shortestDistance(999) {
    Node node = Node();
    previousNode = &node;
}

nodeMap::nodeMap(int shortestDistance, Node* previousVertex) : shortestDistance(shortestDistance), previousNode(previousVertex) {}

Grid::Grid() : Entity(), numRows(35), numColumns(55) {
    init();
}

void Grid::init() {

    // prevents grid from having an even number of rows or columns and
    // from being smaller than 5x5
    if (numRows >= 5 && numColumns >= 5) {
        if (numRows % 2 == 0) {
            numRows++;
        }
        if (numColumns % 2 == 0) {
            numColumns++;
        }
    }
    else {
        numRows = 5;
        numColumns = 5;
    }

    // settings
    setColor(1, 1, 1);
    setWidth(20 * numColumns);
    setHeight(20 * numRows);

    // resize vector of nodes
    nodes.resize(getNumColumns());
    for (int x = 0; x < getNumColumns(); x++) {
        nodes[x].resize(getNumRows());
    }

    createNodes();

}

int Grid::getNumRows() const {
    return numRows;
}

int Grid::getNumColumns() const {
    return numColumns;
}

void Grid::toggleWallNode(int row, int column, bool rDown) {
    // toggles current node to be either a wall or unvisited node,
    // as long as the node is either a wall or unvisted node
    if (nodes[column][row].getNodeType() == UNVISITED && rDown) {
        setNodeType(row, column, WALL);
    }
    else if (nodes[column][row].getNodeType() == WALL && !rDown) {
        setNodeType(row, column, UNVISITED);
    }
}

void Grid::setNodeType(int row, int column, NodeType type) {
    if (row >= 0 && row < nodes[0].size() && column >= 0 && column < nodes.size()) {
        nodes[column][row].setNodeType(type);
    }
}

void Grid::createNodes() {

    // calculate position of start and target nodes
    int middleRow = ((int)ceil((double)numRows / 2.0)) - 1;
    int splitCol = 7;
    point startPosition = {splitCol, middleRow};
    point targetPosition = {numColumns - splitCol - 1, middleRow};

    // populate vector of nodes
    int xPos, yPos, id, x, y;
    xPos = getLeftX() + 10;
    id = 1;
    for (x = 0; x < getNumColumns(); x++) {
        yPos = getTopY() + 10;
        for (y = 0; y < getNumRows(); y++) {
            // create node and set its position
            Node newNode = Node();
            nodes[x][y] = newNode;
            // settings
            nodes[x][y].setPosition(y, x);
            nodes[x][y].setCenterX(xPos);
            nodes[x][y].setCenterY(yPos);
            nodes[x][y].setId(id);
            // determine if its a start or target node
            if (x == startPosition.x && y == startPosition.y) {
                setNodeType(y, x, START);
                startNode = &nodes[x][y];
            }
            else if (x == targetPosition.x && y == targetPosition.y) {
                setNodeType(y, x, TARGET);
                targetNode = &nodes[x][y];
            }
            // increment y position and id
            yPos += 20;
            id++;
        }
        // increment x position
        xPos += 20;
    }

    // adds determines neighbors of each node in grid
    addNeighbors();

}

void Grid::move(int deltaX, int deltaY) {
    // moves grid as well as all nodes
    setCenterX(getCenterX() + deltaX);
    setCenterY(getCenterY() + deltaY);
    for (int x = 0; x < getNumColumns(); x++) {
        for (int y = 0; y < getNumRows(); y++) {
            nodes[x][y].setCenterX(nodes[x][y].getCenterX() + deltaX);
            nodes[x][y].setCenterY(nodes[x][y].getCenterY() + deltaY);
        }
    }
}

void Grid::detectMouse(int x, int y, bool rDown) {

    // calculate which node is being pressed
    int relativeX = x - getLeftX();
    int relativeY = y - getTopY();
    int column = relativeX / 20;
    int row = relativeY / 20;

    // detect which node is being clicked on and toggle it
    toggleWallNode(row, column, rDown);

}

void Grid::addNeighbors() {
    for (int x = 0; x < getNumColumns(); x++) {
        for (int y = 0; y < getNumRows(); y++) {
            // edge cases
            if (x == 0 || y == 0 || x == getNumColumns()-1 || y == getNumRows()-1) {
                // top left corner
                if (x == 0 && y == 0) {
                    nodes[x][y].addNeighbor(&nodes[x+1][y]);
                    nodes[x][y].addNeighbor(&nodes[x][y+1]);
                }
                // top right corner
                else if (x == getNumColumns()-1 && y == 0) {
                    nodes[x][y].addNeighbor(&nodes[x-1][y]);
                    nodes[x][y].addNeighbor(&nodes[x][y+1]);
                }
                // bottom right corner
                else if (x == getNumColumns()-1 && y == getNumRows()-1) {
                    nodes[x][y].addNeighbor(&nodes[x][y-1]);
                    nodes[x][y].addNeighbor(&nodes[x-1][y]);
                }
                // bottom left corner
                else if (x == 0 && y == getNumRows()-1) {
                    nodes[x][y].addNeighbor(&nodes[x][y-1]);
                    nodes[x][y].addNeighbor(&nodes[x+1][y]);
                }
                // top of grid
                else if (y == 0) {
                    nodes[x][y].addNeighbor(&nodes[x+1][y]);
                    nodes[x][y].addNeighbor(&nodes[x][y+1]);
                    nodes[x][y].addNeighbor(&nodes[x-1][y]);
                }
                // left side of grid
                else if (x == getNumColumns()-1) {
                    nodes[x][y].addNeighbor(&nodes[x][y+1]);
                    nodes[x][y].addNeighbor(&nodes[x-1][y]);
                    nodes[x][y].addNeighbor(&nodes[x][y-1]);
                }
                // bottom of grid
                else if (y == getNumRows()-1) {
                    nodes[x][y].addNeighbor(&nodes[x][y-1]);
                    nodes[x][y].addNeighbor(&nodes[x+1][y]);
                    nodes[x][y].addNeighbor(&nodes[x-1][y]);
                }
                // left side of grid
                else if (x == 0) {
                    nodes[x][y].addNeighbor(&nodes[x][y-1]);
                    nodes[x][y].addNeighbor(&nodes[x+1][y]);
                    nodes[x][y].addNeighbor(&nodes[x][y+1]);
                }

            }
            // base case, all nodes except the ones on the border
            else {
                nodes[x][y].addNeighbor(&nodes[x][y-1]);
                nodes[x][y].addNeighbor(&nodes[x+1][y]);
                nodes[x][y].addNeighbor(&nodes[x][y+1]);
                nodes[x][y].addNeighbor(&nodes[x-1][y]);
            }
        }
    }
}

void Grid::reset() {
    // reset grid of nodes
    for (int x = 0; x < getNumColumns(); x++) {
        nodes[x].clear();
    }
    init();
}

void Grid::dijkstras(vector<Node*>& visited, vector<Node*>& path) {

    map<Node*, nodeMap> pathMap;
    vector<Node*>  unvisited;
    Node* currentNode;
    bool targetFound = false;
    int x, y, i, currentShortestDistance, timeout;

    // initialize nodemap
    for (x = 0; x < getNumColumns(); x++) {
        for (y = 0; y < getNumRows(); y++) {
            if (nodes[x][y].getNodeType() == START) {
                pathMap[&nodes[x][y]] = nodeMap(0, &nodes[x][y]);
            }
            else {
                pathMap[&nodes[x][y]] = nodeMap();
            }
        }
    }

    // add all verticies to unvisited vector
    for (x = 0; x < getNumColumns(); x++) {
        for (y = 0; y < getNumRows(); y++) {
            unvisited.push_back(&nodes[x][y]);
        }
    }

    timeout = 0;
    while (!targetFound && timeout < 10000) {

        currentShortestDistance = 999;

        // finds unvisited node with shortest distance from the start
        for (Node* node : unvisited) {
            if (pathMap[node].shortestDistance < currentShortestDistance) {
                currentNode = node;
                currentShortestDistance = pathMap[node].shortestDistance;
            }
        }

        // inspects all neighbors of current vertex
        for (Node* neighbor : currentNode->getNeighbors()) {
            // if target node has been found, stop
            if (neighbor->getNodeType() == TARGET) {
                targetFound = true;
                break;
            }
            if (neighbor->getNodeType() == UNVISITED) {
                // if calculated distance from current neighbor to start node is less
                // than the known distance, then value in the pathMap is replaced
                if (pathMap[currentNode].shortestDistance+1 < pathMap[neighbor].shortestDistance) {
                    pathMap[neighbor].shortestDistance = pathMap[currentNode].shortestDistance + 1;
                    pathMap[neighbor].previousNode = currentNode;
                }
            }
        }

        // sets current node type to visited to update its color in the grid
        if (currentNode->getNodeType() != START && currentNode->getNodeType() != TARGET) {
            visited.push_back(currentNode);
        }

        // remove current node from list of unvisited nodes and add it to visited
        for (i = 0; i < unvisited.size(); i++) {
            if (unvisited[i]->getId() == currentNode->getId()) {
                break;
            }
        }
        unvisited.erase(unvisited.begin()+(i));

        timeout++;

    }

    // adds path nodes to vector
    while (currentNode->getId() != startNode->getId()) {
        path.push_back(currentNode);
        currentNode = pathMap[currentNode].previousNode;
        i++;
    }

}

void Grid::aStar(vector<Node*>& visited, vector<Node*>& path) {

    map<Node*, nodeMap> pathMap;
    vector<Node*>  unvisited;
    Node* currentNode;
    bool targetFound = false;
    int x, y, i, currentShortestDistance, timeout;

    // initialize nodemap
    for (x = 0; x < getNumColumns(); x++) {
        for (y = 0; y < getNumRows(); y++) {
            if (nodes[x][y].getNodeType() == START) {
                pathMap[&nodes[x][y]] = nodeMap(0, &nodes[x][y]);
            }
            else {
                pathMap[&nodes[x][y]] = nodeMap();
            }
        }
    }

    // add all verticies to unvisited vector
    for (x = 0; x < getNumColumns(); x++) {
        for (y = 0; y < getNumRows(); y++) {
            unvisited.push_back(&nodes[x][y]);
        }
    }

    timeout = 0;
    while (!targetFound && timeout < 10000) {

        currentShortestDistance = 999;

        // finds unvisited node with shortest distance from the start
        for (Node* node : unvisited) {
            if (pathMap[node].shortestDistance < currentShortestDistance) {
                currentNode = node;
                currentShortestDistance = pathMap[node].shortestDistance;
            }
        }

        // inspects all neighbors of current vertex
        for (Node* neighbor : currentNode->getNeighbors()) {
            // if target node has been found, stop
            if (neighbor->getNodeType() == TARGET) {
                targetFound = true;
                break;
            }
            if (neighbor->getNodeType() == UNVISITED) {
                // if calculated distance from current neighbor to start node is less
                // than the known distance, then value in the pathMap is replaced
                if (pathMap[currentNode].shortestDistance+1 < pathMap[neighbor].shortestDistance) {
                    pathMap[neighbor].shortestDistance = pathMap[currentNode].shortestDistance + 1;
                    pathMap[neighbor].previousNode = currentNode;
                }
            }
        }

        // sets current node type to visited to update its color in the grid
        if (currentNode->getNodeType() != START && currentNode->getNodeType() != TARGET) {
            visited.push_back(currentNode);
        }

        // remove current node from list of unvisited nodes and add it to visited
        for (i = 0; i < unvisited.size(); i++) {
            if (unvisited[i]->getId() == currentNode->getId()) {
                break;
            }
        }
        unvisited.erase(unvisited.begin()+(i));

        timeout++;

    }

    // adds path nodes to vector
    while (currentNode->getId() != startNode->getId()) {
        path.push_back(currentNode);
        currentNode = pathMap[currentNode].previousNode;
        i++;
    }

}

void Grid::breadthFirst(vector<Node*>& visited, vector<Node*>& path) {
    for (int x = 0; x < getNumColumns(); x++) {
        for (int y = 0; y < getNumRows(); y++) {
            nodes[x][y].setNodeType(WALL);
        }
    }
}

void Grid::depthFirst(vector<Node*>& visited, vector<Node*>& path) {
    for (int x = 0; x < getNumColumns(); x++) {
        for (int y = 0; y < getNumRows(); y++) {
            nodes[x][y].setNodeType(START);
        }
    }
}

void Grid::draw() const {

    int x, y;

    // draw nodes
    for (x = 0; x < getNumColumns(); x++) {
        for (y = 0; y < getNumRows(); y++) {
            nodes[x][y].draw();
        }
    }

    // draw vertical lines of grid
    for (x = getLeftX(); x <= getRightX(); x+=20) {
        glBegin(GL_QUADS);
        glColor3f(getRed(), getGreen(), getBlue());
        glVertex2f(x+1, getTopY());
        glVertex2f(x, getTopY());
        glVertex2f(x, getBottomY()+1);
        glVertex2f(x+1, getBottomY()+1);
        glEnd();
    }

    // draw horizontal lines of grid
    for (y = getTopY(); y <= getBottomY(); y+=20) {
        glBegin(GL_QUADS);
        glColor3f(getRed(), getGreen(), getBlue());
        glVertex2f(getRightX(), y + 1);
        glVertex2f(getLeftX(), y + 1);
        glVertex2f(getLeftX(), y);
        glVertex2f(getRightX(), y);
        glEnd();
    }

}