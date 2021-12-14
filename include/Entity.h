#ifndef PATHFINDING_ENTITY_H
#define PATHFINDING_ENTITY_H

#include "graphics.h"

struct dimension {

    int width, height;

    dimension();
    dimension(int width, int height);

};

struct point {

    int x, y;

    point();
    point(int x, int y);

};

struct color {

    double r, g, b, a;

    color();
    color(double r, double g, double b);
    color(double r, double g, double b, double a);

};

class Entity {

protected:

    dimension size;
    point center;
    color fill;

public:

    Entity();
    Entity(point center);
    Entity(color fill);
    Entity(point center, color fill);
    Entity(dimension size, point center, color fill);

    virtual ~Entity() = default;

    dimension getDimensions() const;
    void setDimensions(dimension size);
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    point getCenter() const;
    void setCenter(point center);
    int getCenterX() const;
    int getCenterY() const;
    void setCenterX(int x);
    void setCenterY(int y);
    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    void setColor(color fill);
    void setColor(double r, double g, double b);
    void setColor(double r, double g, double b, double a);
    color getColor() const;
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    double getAlpha() const;

    bool isOverlapping(int x, int y) const;

    virtual void draw() const = 0;

};

#endif //PATHFINDING_ENTITY_H
