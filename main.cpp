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
int visitedIndex, pathIndex, drawSpeed, tempSpeed;
bool visitedDrawn, pathDrawn, rButtonDown, lButtonDown;
TextBox title, run, reset, unvisited, visited, start, target, wall, path;
Dropdown algorithm, speed;
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
    algorithm = Dropdown();
    algorithm.setColor(black);
    algorithm.setWidth(200);
    algorithm.setHeight(70);
    algorithm.setCenterX(width - 400);
    algorithm.setCenterY(55);
    algorithm.addOption({"Dijkstra", 5.0});
    algorithm.addOption({"A* Search", 5.0});
    algorithm.addOption({"Breadth First", 5.0});
    algorithm.addOption({"Depth First", 5.0});
    entities.push_back(&algorithm);
}

void initSpeed() {
    speed = Dropdown();
    speed.setColor(black);
    speed.setWidth(200);
    speed.setHeight(70);
    speed.setCenterX(width - 650);
    speed.setCenterY(55);
    speed.addOption({"Fast", 5.5});
    speed.addOption({"Medium", 7.0});
    speed.addOption({"Slow", 5.5});
    entities.push_back(&speed);
}

void init() {

    // sets window dimensions and initializes app and settings
    width = 1200;
    height = 1000;
    srand(time(0));

    // entities & settings initialized
    screen = HOME;
    drawSpeed = 10;
    rButtonDown = false;
    lButtonDown = false;

    initTitle();
    initRun();
    initReset();
    initKey();
    initGrid();
    initDropdown();
    initSpeed();

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
    if (reset.isOverlapping(x, y) && screen != SORT) {
        reset.setColor(hoverFill);
    }
    else {
        reset.setColor(black);
    }

    // change speed color when menu is closed
    if (screen == HOME) {
        if (!speed.isOpen()) {
            if (speed.isOverlapping(x, y)) {
                speed.setOptionColor(0, hoverFill);
            }
            else {
                speed.setOptionColor(0, black);
            }
        }
        else if (speed.isOpen()) {
            if (speed.isOverlapping(x, y)) {
                // highlights option being hovered
                speed.hover(x, y);
            }
        }
    }

    // change algorithm color when menu is closed
    if (screen == HOME) {
        if (!algorithm.isOpen()) {
            if (algorithm.isOverlapping(x, y)) {
                algorithm.setOptionColor(0, hoverFill);
            }
            else {
                algorithm.setOptionColor(0, black);
            }
        }
        else if (algorithm.isOpen()) {
            if (algorithm.isOverlapping(x, y)) {
                // highlights option being hovered
                algorithm.hover(x, y);
            }
        }
    }

    // drawing & removing wall nodes
    if (lButtonDown && !rButtonDown) {
        grid.detectMouse(x, y, true);
    }
    if (rButtonDown && !lButtonDown) {
        grid.detectMouse(x, y, false);
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    // create wall node
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && grid.isOverlapping(x, y) && screen == HOME && !rButtonDown) {
        if (lButtonDown) {
            lButtonDown = false;
        }
        else {
            lButtonDown = true;
        }
    }
    // delete wall node
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && grid.isOverlapping(x, y) && screen == HOME && !lButtonDown) {
        if (rButtonDown) {
            rButtonDown = false;
        }
        else {
            rButtonDown = true;
        }
    }
    // press button
    for (TextBox* thisButton : buttons) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && thisButton->isOverlapping(x, y)) {
            if (thisButton->getText() == "Run" && screen == HOME) {
                thisButton->setColor(pressFill);
                if (algorithm.getCurrentOption().text == "Dijkstra") {
                    grid.dijkstras(visitedNodes, pathNodes);
                }
                else if (algorithm.getCurrentOption().text == "A* Search") {
                    grid.aStar(visitedNodes, pathNodes);
                }
                else if (algorithm.getCurrentOption().text == "Breadth First") {
                    grid.breadthFirst(visitedNodes, pathNodes);
                }
                else if (algorithm.getCurrentOption().text == "Depth First") {
                    grid.depthFirst(visitedNodes, pathNodes);
                }
                screen = SORT;
                visitedIndex = 0;
                pathIndex = pathNodes.size();
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
    // press algorithm dropdown
    if (screen == HOME) {
        if (algorithm.isOverlapping(x, y)) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == HOME) {
                if (algorithm.isOpen()) {
                    // drop down is open
                    algorithm.press(x, y);
                }
                else {
                    // dropdown is closed
                    algorithm.setOptionColor(0, pressFill);
                    algorithm.toggle();
                }
            }
            else {
                for (int i = 0; i < algorithm.getOptions().size(); i++) {
                    algorithm.setOptionColor(i, black);
                }
            }
        }
    }

    // click speed dropdown
    if (screen == HOME) {
        if (speed.isOverlapping(x, y)) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == HOME) {
                if (speed.isOpen()) {
                    // drop down is open
                    speed.press(x, y);
                    if (speed.getCurrentOption().text == "Fast") {
                        drawSpeed = 10;
                    }
                    else if (speed.getCurrentOption().text == "Medium") {
                        drawSpeed = 20;
                    }
                    else {
                        drawSpeed = 30;
                    }
                }
                else {
                    // dropdown is closed
                    speed.setOptionColor(0, pressFill);
                    speed.toggle();
                }
            }
            else {
                for (int i = 0; i < speed.getOptions().size(); i++) {
                    speed.setOptionColor(i, black);
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
            if (pathIndex == pathNodes.size()) {
                tempSpeed = drawSpeed;
                drawSpeed = 30;
            }
            if (pathIndex < 2) {
                drawSpeed = tempSpeed;
            }
            while (pathIndex > 0) {
                pathIndex--;
                pathNodes[pathIndex]->setNodeType(PATH);
                break;
            }
        }
        if (visitedIndex == visitedNodes.size() && pathIndex == 0) {
            screen = DONE;
        }
    }

    glutTimerFunc(drawSpeed, pathTimer, dummy);
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