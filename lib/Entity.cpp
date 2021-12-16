#include "Entity.h"

dimension::dimension() : width(20), height(20) {}

point::point() : x(600), y(500) {}

point::point(int x, int y) : x(x), y(y) {}

color::color() : r(1.0), g(1.0), b(1.0), a(1.0) {}

color::color(double r, double g, double b) : r(r), g(g), b(b), a(1.0) {}

color::color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}

Entity::Entity() : size(dimension()), center(point()), fill(color()) {}

Entity::Entity(point center) : size(dimension()), center(center), fill(color()) {}

Entity::Entity(color fill) : size(dimension()), center(point()), fill(fill) {}

Entity::Entity(point center, color fill) : size(dimension()), center(center), fill(color()) {}

Entity::Entity(dimension size, point center, color fill) : size(size), center(center), fill(fill) {}

int Entity::getHeight() const {
    return size.height;
}

void Entity::setHeight(int height) {
    size.height = height;
}

int Entity::getWidth() const {
    return size.width;
}

void Entity::setWidth(int width) {
    size.width = width;
}

void Entity::setCenter(point center) {
    this->center = center;
}

int Entity::getCenterX() const {
    return center.x;
}

int Entity::getCenterY() const {
    return center.y;
}

void Entity::setCenterX(int x) {
    center.x = x;
}

void Entity::setCenterY(int y) {
    center.y = y;
}

int Entity::getLeftX() const {
    return center.x - getWidth() / 2;
}

int Entity::getRightX() const {
    return center.x + getWidth() / 2;
}

int Entity::getTopY() const {
    return center.y - getHeight() / 2;
}

int Entity::getBottomY() const {
    return center.y + getHeight() / 2;
}

void Entity::setColor(color fill) {
    this->fill = fill;
}

void Entity::setColor(double r, double g, double b) {
    fill.r = r;
    fill.g = g;
    fill.b = b;
}

double Entity::getRed() const {
    return fill.r;
}

double Entity::getGreen() const {
    return fill.g;
}

double Entity::getBlue() const {
    return fill.b;
}

bool Entity::isOverlapping(int x, int y) const {
    if (x >= getLeftX() && x <= getRightX() && y >= getTopY() && y <= getBottomY()) {
        return true;
    }
    else {
        return false;
    }
}