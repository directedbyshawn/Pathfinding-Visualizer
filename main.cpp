#include <iostream>
#include <memory>


#include "TextBox.h"
#include "Dropdown.h"
#include "Grid.h"

using namespace std;

GLdouble width, height;
int wd;

// entities & settings
vector<Entity*> entities;
vector<TextBox*> buttons;
Grid grid;
vector<Node*> visitedNodes, pathNodes;
int visitedIndex, pathIndex;
bool visitedDrawn, pathDrawn;
TextBox title, run, reset, unvisited, visited, start, target, wall, path;
Dropdown dropdown;
Node exUnvisited, exVisited, exStart, exTarget, exWall, exPath;
State screen;
int gridX, gridY = 0;

const color bg = {26.0/255, 26.0/255.0, 26.0/255.0, 1.0};
const color black = {0, 0, 0};
const color hoverFill = {120.0/255.0, 120.0/255.0, 120.0/255.0};
const color pressFill = {90.0/255.0, 90.0/255.0, 90.0/255.0};

void initGrid() {
    grid = Grid();
    grid.move(0, 100);
    grid.reset();
    entities.push_back(&grid);
}

void initTitle() {
    title = TextBox("Pathfinding Visualizer");
    title.setWidth(275);
    title.setHeight(70);
    title.setOffset(4.9);
    title.setCenter({155, 55});
    entities.push_back(&title);
}

void initRun() {
    run = TextBox("Run");
    run.setWidth(100);
    run.setHeight(70);
    run.setOffset(6.8);
    run.setCenter({(int)width - 200, 55});
    entities.push_back(&run);
    buttons.push_back(&run);
}

void initReset() {
    reset = TextBox("Reset");
    reset.setWidth(120);
    reset.setHeight(70);
    reset.setOffset(5.5);
    reset.setCenter({(int)width - 75, 55});
    entities.push_back(&reset);
    buttons.push_back(&reset);
}

void initKey() {

    // create example nodes
    exUnvisited = Node();
    exVisited = Node();
    exStart = Node();
    exTarget = Node();
    exWall = Node();
    exPath = Node();

    // create textbox labes for each node
    unvisited = TextBox("Unvisited");
    visited = TextBox("Visited");
    start = TextBox("Start");
    target = TextBox("Target");
    wall = TextBox("Wall");
    path = TextBox("Path");

    // set textbox color
    unvisited.setColor(bg);
    visited.setColor(bg);
    start.setColor(bg);
    target.setColor(bg);
    wall.setColor(bg);
    path.setColor(bg);

    // configure textbox settings
    int genOffset = 5.0;
    unvisited.setOffset(genOffset);
    visited.setOffset(genOffset);
    start.setOffset(genOffset);
    target.setOffset(genOffset);
    wall.setOffset(genOffset);
    path.setOffset(genOffset);

    // set types
    exVisited.setNodeType(VISITED);
    exStart.setNodeType(START);
    exTarget.setNodeType(TARGET);
    exWall.setNodeType(WALL);
    exPath.setNodeType(PATH);

    int space = 60;
    int y = 150;
    int offset = 30;

    // set node position
    exUnvisited.setCenter({(int)width/2 - 5*space, y});
    exVisited.setCenter({(int)width/2 - 3*space, y});
    exStart.setCenter({(int)width/2 - space, y});
    exTarget.setCenter({(int)width/2 + space, y});
    exWall.setCenter({(int)width/2 + 3*space, y});
    exPath.setCenter({(int)width/2 + 5*space, y});

    // set text position
    unvisited.setCenter({exUnvisited.getCenterX(), exUnvisited.getCenterY() + offset});
    visited.setCenter({exVisited.getCenterX(), exVisited.getCenterY() + offset});
    start.setCenter({exStart.getCenterX(), exStart.getCenterY() + offset});
    target.setCenter({exTarget.getCenterX(), exTarget.getCenterY() + offset});
    wall.setCenter({exWall.getCenterX(), exWall.getCenterY() + offset});
    path.setCenter({exPath.getCenterX(), exPath.getCenterY() + offset});

    entities.push_back(&exUnvisited);
    entities.push_back(&exVisited);
    entities.push_back(&exStart);
    entities.push_back(&exTarget);
    entities.push_back(&exWall);
    entities.push_back(&exPath);

    entities.push_back(&unvisited);
    entities.push_back(&visited);
    entities.push_back(&start);
    entities.push_back(&target);
    entities.push_back(&wall);
    entities.push_back(&path);

}

void initDropdown() {
    dropdown = Dropdown();
    dropdown.setColor(black);
    dropdown.setWidth(200);
    dropdown.setHeight(70);
    dropdown.setCenterX(width - 400);
    dropdown.setCenterY(55);
    dropdown.addOption({"Dijkstra", 5.0});
    dropdown.addOption({"A* Search", 5.0});
    dropdown.addOption({"Breadth First", 5.0});
    dropdown.addOption({"Depth First", 5.0});
    entities.push_back(&dropdown);
}

void init() {

    // sets window dimensions and initializes app and settings
    width = 1200;
    height = 1000;
    srand(time(0));

    // entities & settings initialized
    screen = HOME;

    initTitle();
    initRun();
    initReset();
    initKey();
    initGrid();
    initDropdown();

}

void initGL() {

    // background color of window
    glClearColor(bg.r, bg.g, bg.b, bg.a);

}

void display() {

    // OpenGL settings
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (Entity* entity : entities) {
        entity->draw();
    }

    glFlush();

}

void kbd(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    glutPostRedisplay();
}

void cursor(int x, int y) {

    // change run button color when hovering
    if (run.isOverlapping(x, y) && screen == HOME) {
        run.setColor(hoverFill);
    }
    else {
        run.setColor(black);
    }

    // change reset button color when hovering
    if (reset.isOverlapping(x, y)) {
        reset.setColor(hoverFill);
    }
    else {
        reset.setColor(black);
    }


    // change dropdown color when menu is closed
    if (screen == HOME) {
        if (!dropdown.isOpen()) {
            if (dropdown.isOverlapping(x, y)) {
                dropdown.setOptionColor(0, hoverFill);
            }
            else {
                dropdown.setOptionColor(0, black);
            }
        }
        else if (dropdown.isOpen()) {
            if (dropdown.isOverlapping(x, y)) {
                // highlights option being hovered
                dropdown.hover(x, y);
            }
        }
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    // create wall node
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && grid.isOverlapping(x, y) && screen == HOME) {
        grid.detectMouse(x, y, true);
    }
    // delete wall node
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && grid.isOverlapping(x, y) && screen == HOME) {
        grid.detectMouse(x, y, false);
    }
    // press button
    for (TextBox* thisButton : buttons) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && thisButton->isOverlapping(x, y)) {
            if (thisButton->getText() == "Run" && screen == HOME) {
                thisButton->setColor(pressFill);
                if (dropdown.getCurrentOption().text == "Dijkstra") {
                    grid.dijkstras(visitedNodes, pathNodes);
                }
                else if (dropdown.getCurrentOption().text == "A* Search") {
                    grid.aStar();
                }
                else if (dropdown.getCurrentOption().text == "Breadth First") {
                    grid.breadthFirst();
                }
                else if (dropdown.getCurrentOption().text == "Depth First") {
                    grid.depthFirst();
                }
                screen = SORT;
                visitedIndex = 0;
                pathIndex = 0;
            }
            else if (thisButton->getText() == "Reset" && (screen == HOME || screen == DONE)) {
                screen = HOME;
                thisButton->setColor(pressFill);
                grid.reset();
                visitedNodes.clear();
                pathNodes.clear();
            }
        }
        else {
            thisButton->setColor(black);
        }
    }
    // press dropdown
    if (screen == HOME) {
        if (dropdown.isOverlapping(x, y)) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == HOME) {
                if (dropdown.isOpen()) {
                    // drop down is open
                    dropdown.press(x, y);
                }
                else {
                    // dropdown is closed
                    dropdown.setOptionColor(0, pressFill);
                    dropdown.toggle();
                }
            }
            else {
                for (int i = 0; i < dropdown.getOptions().size(); i++) {
                    dropdown.setOptionColor(i, black);
                }
            }
        }
    }

    glutPostRedisplay();
}

void pathTimer(int dummy) {

    // sets all of the visited nodes and then sets all of the path nodes, redraws grid
    // after each node is changed to emulate animation
    if (screen == SORT) {
        while (visitedIndex < visitedNodes.size()) {
            visitedNodes[visitedIndex]->setNodeType(VISITED);
            visitedIndex++;
            break;
        }
        if (visitedIndex == visitedNodes.size()) {
            while (pathIndex < pathNodes.size()) {
                pathNodes[pathIndex]->setNodeType(PATH);
                pathIndex++;
                break;
            }
        }
        if (visitedIndex == visitedNodes.size() && pathIndex == pathNodes.size()) {
            screen = DONE;
        }
    }

    glutTimerFunc(10, pathTimer, dummy);
    glutPostRedisplay();

}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(500, 200);

    wd = glutCreateWindow("Path Finding Visualizer");

    glutDisplayFunc(display);

    initGL();

    glutKeyboardFunc(kbd);
    glutSpecialFunc(kbdS);
    glutPassiveMotionFunc(cursor);
    glutMouseFunc(mouse);

    glutTimerFunc(0, pathTimer, 0);

    glutMainLoop();

}