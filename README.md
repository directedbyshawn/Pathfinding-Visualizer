# Pathfinding Visualizer

<img alt="screenshot of application" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/sc1.jpg" style="width: 500px; margin: 30px;">

## Description
This is a visualization tool to help enhance and demonstrate my knowledge of pathfinding algorithms. The program works by creating a
two-dimensional grid populated with nodes of equal size. Each node has a theoretical edge connecting it to its
neighboring nodes with a weight of 1. The grid has a start node and a target node, and the user is allowed to draw
wall nodes anywhere else on the grid. The algorithm will then find the shortest path between the start and 
target node and draw it for the user to see on the screen. The nodes that have been visited are also visible on the
screen so the user can get a feel for what is happening in the algorithm in real time. 

## Purpose
The purpose of this project was to enhance and demonstrate my understanding of pathfinding algorithms. While I did
learn a lot about implementing such algorithms, I spent more time creating the GUI which was much more time-consuming
and complicated than I had anticipated.

## Directions
The only library used in this project is OpenGL. `CMakeLists.txt`
is already configured to run on both apple and windows machines if you compile your projects with CMake, however I have not tested it on apple machines so
I cannot verify that it will run successfully. 


