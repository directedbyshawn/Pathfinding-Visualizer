# Pathfinding Visualizer (WIP)

<img alt="screenshot of application" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/sc1.jpg" style="width: 500px; margin: 30px;">

## Description
For my cs 120 final project I created a pathfinding visualizer for Dijkstra's shortest path algorithm. While I originally
planned to implement more algorithm's, I only had time to get dijkstra's working. The program works by creating a
two-dimensional grid populated with nodes of equal size. Each node has a theoretical edge connecting it to its
neighboring nodes with a weight of 1. The grid has a start node and a target node, and the user is allowed to draw
wall nodes anywhere else on the grid. Dijkstra's algorithm will then find the shortest path between the start and 
target node and draw it for the user to see on the screen. The nodes that have been visited are also visible on the
screen so the user can get a feel for what is happening in the algorithm in real time. 

## Purpose
The purpose of this project was to enhance and demonstrate my understanding of pathfinding algorithms. While I did
learn a lot about implementing such algorithms, I spent more time creating the GUI which was much more time-consuming
and complicated than I had anticipated. I also wanted to create a project that would be a good resume project, and 
I have heard repeatedly online that companies love to see visual projects that demonstrate an understanding of 
algorithms. 

## Directions
The only libraries used in this project are OpenGL and GLUT, which we have used extensively in class. `CMakeLists.txt`
is already configured to run on both apple and windows machines, however I have not tested it on apple machines so
I cannot verify that it will run successfully. All you really need to do is put `freeglut.dll` into your debug folder and
the project should compile and run. Once it runs, you are presented with a grid with a starting node and target node, 
with the rest of the nodes being unvisited. I included a key to explain which nodes are what color. You can draw
wall nodes with the left mouse button, and turn them back into unvisited nodes using the right mouse button. When
you have drawn all the wall nodes you wish, you hit run in the top right to run dijkstra's. As previously stated, 
dijkstra's algorithm was implemented so only that dropdown option will perform the algorithm. Once the algorithm 
finishes and draws out the shortest path, you can reset the grid with the reset button. Make sure when you are drawing
wall nodes that it is possible to reach the target node from the starting node. I hope in the future to add an algorithm that
ensures that a path from the start to target is possible, but I couldn't figure it out in time to submit this project.

## Documentation and planning
The UML diagram is not the most useful. My subscription ran out on lucidchart so I only had one style of arrow to use, making
it difficult to differentiate inheritance/aggregation/composition. I also did not stick strictly to the diagrams nor
did I update them after making changes to the code. However, they served very well as an outline when I was first planning
the project. The GUI design on the other hand is quite similar to my plan.
<div style="width: 500px;">
    <img alt="screenshot of GUI plan" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/gui-plan.png" style="width: 100%; margin: 30px;">
    <img alt="screenshot of UML Diagram" src="https://srodgers.w3.uvm.edu/cs120/pathfinding-images/uml.png" style="width: 100%; margin: 30px;">
</div>

## TODO
 - [ ] Add dropdown for speed 
 - [ ] Make it so that when you click on the grid you toggle drawing or not drawing walls instead of clicking for each wall
 - [ ] Implement more algorithms
 - [ ] Add method docs to header files
