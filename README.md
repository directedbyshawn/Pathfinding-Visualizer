# Pathfinding Visualizer

<img alt="screenshot of application" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/sc2.png" style="width: 500px; margin: 30px;">

## Description
This is a visualization tool to help enhance and demonstrate my knowledge of pathfinding algorithms. The program works by creating a
two-dimensional grid populated with nodes. Each node has an edge connecting it to its
direct neighbor nodes with a weight of 1. The grid has a start node and a target node, and the user is allowed to draw
wall nodes anywhere else on the grid. The algorithms will then find a path between the start and 
target node. Some algorithms guarantee the shortest path while others don't. The visited nodes animate in order of traversal to give
the user a feel for how the algorithm works. 

## Complexity Analysis
In the traditional implementation of Dijkstra's algorithm, you get a runtime complexity of $\theta (n+m)$, where $n$ is the number of nodes in the 
graph and $m$ is the number of edges. In this implementation, it runs in $O(n+m)$. This is because the algorithm terminates when the target node
is found, so it almost never searches every node and every edge. A* search also runs in $O(n+m)$. While these two algorithms have the same
runtime complexity, A* will almost always run faster, as it has an added heuristic. The heuristic determines the theoretical optimal path from
any node to the target node, disregarding the concept of wall nodes. This allows the algorithm to prioritize nodes close to the target node as opposed
to Dijkstra's, which searches breadth first.

## Purpose
The purpose of this project was to enhance and demonstrate my understanding of pathfinding algorithms. It taught me a great deal about
pathfinding algorithms, complexity analysis, and creating UI elements from scratch.

## Directions
The only library used in this project is OpenGL. All of the display elements were created from scratch using OpenGL. `CMakeLists.txt`
is already configured to run on both Mac and Windows machines if you compile your projects with CMake.

## Demo

<iframe width="560" height="315" src="https://www.youtube.com/embed/NpZ87BABE80" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen>
</iframe>

<p> Click <a href="https://youtu.be/NpZ87BABE80" target="_blank">here</a> for a short 2 minute video demo of the tool! </p>

