#ifndef CODE_GRAPHICS_H
#define CODE_GRAPHICS_H

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

enum State {HOME, SORT, DONE};
enum NodeType {UNVISITED, VISITED, START, TARGET, WALL, PATH};

/**
 * Initializes grid
 */
void initGrid();

/**
 * Initializes title in top left
 */
void initTitle();

/**
 * Initializes run button
 */
void initRun();

/**
 * Initializes reset button
 */
void initReset();

/**
 * Initializes speed selection dropdown
 */
void initSpeed();

/**
 * Initializes key that labels each node and its type
 */
void initKey();

/**
 * Initializes algorithm selection drop down
 */
void initDropdown();

/**
 * Timer that helps
 * @param dummy recursion param
 */
void pathTimer(int dummy);

/**
 * Initializes game settings and calls all initialization helper functions
 */
void init();

/**
 * Initializes window background & color
 */
void initGL();

/**
 * callback function to render objects to screen
 */
void display();

/**
 * Retrieves key presses
 *
 * @param key key pressed
 * @param x x coordinate of mouse relative to window
 * @param y y coordinate or mouse relative to window
 */
void kbd(unsigned char key, int x, int y);

/**
 * Retrieves key presses (arrows, function keys etc)
 *
 * @param key key pressed
 * @param x x coordinate of mouse relative to window
 * @param y y coordinate or mouse relative to window
 */
void kbsS(int key, int x, int y);

/**
 * Callback function that is triggered whenever mouse moves in window
 *
 * @param x x coordinate of mouse relative to window
 * @param y y coordinate or mouse relative to window
 */
void cursor(int x, int y);

/**
 * Callback function that is triggered whenever the mouse buttons are pressed
 *
 * @param button mouse button pressed
 * @param state state of mouse button (down, up etc)
 * @param x x coordinate of mouse when event was triggered
 * @param y y coordinate of mouse when event was triggered
 */
void mouse(int button, int state, int x, int y);

#endif //CODE_GRAPHICS_H
