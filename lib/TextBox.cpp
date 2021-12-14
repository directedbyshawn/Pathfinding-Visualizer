#include "TextBox.h"

TextBox::TextBox() : Entity({0, 0, 0}), text("Default Message"), stringColor(1, 1, 1), offset(4.0) {}

TextBox::TextBox(std::string text) : Entity({0, 0, 0}), text(text), stringColor(1, 1, 1), offset(4.0)  {}

TextBox::TextBox(std::string text, color stringColor) : Entity({0, 0, 0}), text(text), stringColor(stringColor), offset(4.0)  {}

TextBox::TextBox(std::string text, color stringColor, point center, color fill) : Entity(center, fill), text(text), stringColor(stringColor), offset(4.0)  {}

void TextBox::setText(std::string text) {
    this->text = text;
}

std::string TextBox::getText() const {
    return this->text;
}

void TextBox::setOffset(double offset) {
    this->offset = offset;
}

double TextBox::getOffset() const {
    return offset;
}

void TextBox::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void TextBox::draw() const {

    // draw box
    glBegin(GL_QUADS);
    glColor3f(getRed(), getGreen(), getBlue());
    glVertex2f(getRightX(), getTopY());
    glVertex2f(getLeftX(), getTopY());
    glVertex2f(getLeftX(), getBottomY());
    glVertex2f(getRightX(), getBottomY());
    glEnd();

    // draw text
    glColor3f(stringColor.r, stringColor.g, stringColor.b);
    glRasterPos2i(center.x - (offset * text.length()), center.y + 7);
    for (const char &letter : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }

}