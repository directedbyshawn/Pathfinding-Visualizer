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

void initGrid();
void initTitle();
void initRun();
void initReset();
void initSpeed();
void initKey();
void initDropdown();

void pathTimer(int dummy);

// glut functions
void init();
void initGL();
void display();
void kbd(unsigned char key, int x, int y);
void kbsS(int key, int x, int y);
void cursor(int x, int y);
void mouse(int button, int state, int x, int y);

#endif //CODE_GRAPHICS_H
