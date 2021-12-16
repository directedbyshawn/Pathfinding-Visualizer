/*
 *
 * This class is a super class used to represent any user defined that will be rendered to the
 * screen. Since all objects rendered have dimensions, size, and color, it made sense to include
 * them all under one class which I have defined as entity. Node, Grid, Dropdown, and Textbox are
 * all subclasses of entity as they have all the qualities previously stated.
 *
 */

#ifndef PATHFINDING_ENTITY_H
#define PATHFINDING_ENTITY_H

#include "graphics.h"

struct dimension {

    int width, height;

    /**
     * Initializes dimensions to be 20x20 pixels.
     */
    dimension();


};

struct point {

    int x, y;

    /**
     * Initializes point to be the center of the screen (600, 500)
     */
    point();

    /**
     * Initializes point at specific point on the screen
     *
     * @param x x value of point
     * @param y y value of point
     */
    point(int x, int y);

};

struct color {

    double r, g, b, a;

    /**
     * Initializes color as white (1, 1, 1, 1).
     */
    color();

    /**
     * Initializes as RGB color with 1.0 Alpha.
     *
     * @param r red value
     * @param g green value
     * @param b blue value
     */
    color(double r, double g, double b);

    /**
     * Initializes as RGBA color.
     *
     * @param r red value
     * @param g green value
     * @param b blue value
     * @param a alpha value
     */
    color(double r, double g, double b, double a);

};

class Entity {

protected:

    dimension size;
    point center;
    color fill;

public:

    /**
     * Default constructor,
     */
    Entity();

    /**
     * Initializes entity as white and 20x20 with custom center point
     *
     * @param center center point of entity
     */
    Entity(point center);

    /**
     * Initializes entity as 20x20 and at the center of the screen with custom color
     *
     * @param fill entity color
     */
    Entity(color fill);

    /**
     * Initializes entity as 20x20 at custom center with custom color
     *
     * @param center center point of entity
     * @param fill entity color
     */
    Entity(point center, color fill);

    /**
     * Initializes entity with custom dimensions, center point, and color
     *
     * @param size 2D dimension of entity
     * @param center center point of entity
     * @param fill entity color
     */
    Entity(dimension size, point center, color fill);

    virtual ~Entity() = default;

    /**
     *
     * @return height of entity
     *
     */
    int getHeight() const;

    /**
     *
     * @param height height of entity
     *
     */
    void setHeight(int height);

    /**
     *
     * @return width of entity
     *
     */
    int getWidth() const;

    /**
     *
     * @param width width of entity
     *
     */
    void setWidth(int width);

    /**
     *
     * @param center center point of entity
     *
     */
    void setCenter(point center);

    /**
     *
     * @return x value of center point
     *
     */
    int getCenterX() const;

    /**
     *
     * @return y value of center point
     *
     */
    int getCenterY() const;

    /**
     *
     * @param x x value of center point
     *
     */
    void setCenterX(int x);

    /**
     *
     * @param y y value of center point
     *
     */
    void setCenterY(int y);

    /**
     *
     * @return left most x value of entity
     *
     */
    int getLeftX() const;

    /**
     *
     * @return right most x value of entity
     *
     */
    int getRightX() const;

    /**
     *
     * @return lowest y value of entity
     *
     */
    int getTopY() const;

    /**
     *
     * @return highest y value of entity
     *
     */
    int getBottomY() const;

    /**
     * Sets entities color
     *
     * @param fill new color of entity
     */
    void setColor(color fill);

    /**
     * Sets entities color by each rgb value
     *
     * @param r new red value
     * @param g new green value
     * @param b new blue value
     */
    void setColor(double r, double g, double b);

    /**
     *
     * @return red value of entities RGB value
     *
     */
    double getRed() const;

    /**
     *
     * @return green value of entities RGB value
     *
     */
    double getGreen() const;

    /**
     *
     * @return blue value of entities RGB value
     *
     */
    double getBlue() const;

    /**
     * Determines if a certain 2D point on the plane is overlapping
     * with the entity.
     *
     * @param x x value to be checked
     * @param y y value to be checked
     * @return T/F is the point overlapping with the entity
     */
    bool isOverlapping(int x, int y) const;

    /**
     * Pure virtual method, all entities are drawn differently to the screen.
     */
    virtual void draw() const = 0;

};

#endif //PATHFINDING_ENTITY_H
