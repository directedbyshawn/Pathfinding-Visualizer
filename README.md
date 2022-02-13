# Pathfinding Visualizer

<img alt="screenshot of application" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/sc2.png" style="width: 500px; margin: 30px;">

## Description
This is a visualization tool to help enhance and demonstrate my knowledge of pathfinding algorithms. The program works by creating a
two-dimensional grid populated with nodes. Each node has an edge connecting it to its
direct neighbor nodes with a weight of 1. The grid has a start node and a target node, and the user is allowed to draw
wall nodes anywhere else on the grid. The algorithms will then find a path between the start and 
target node. Some algoritms guarantee the shortest path while others don't. The visited nodes animate in order of traversal to give
the user a feel for how the algorithm works. 

## Purpose
The purpose of this project was to enhance and demonstrate my understanding of pathfinding algorithms. It taught me a great deal about
pathfinding algorithms, complexity analysis, and creating display elements from scratch.

## Directions
The only library used in this project is OpenGL. All of the display elements were created from scratch using OpenGL. `CMakeLists.txt`
is already configured to run on both apple and windows machines if you compile your projects with CMake.

