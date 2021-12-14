#include "Dropdown.h"

option::option() : text("None"), offset(4.0), bg({0, 0, 0}) {}

option::option(std::string text, double offset) : text(text), offset(offset), bg({0, 0, 0}) {}

Dropdown::Dropdown() : Entity(), currentOption(option()), open(false) {}

void Dropdown::addOption(option option) {
    // adds option to dropdown
    options.push_back(option);
    if (options.size() == 1) {
        setCurrentOption(option);
    }
}

std::vector<option> Dropdown::getOptions() const {
    return options;
}

bool Dropdown::isOpen() const {
    return open;
}

void Dropdown::toggle() {
    // changes dimensions based on if the dropdown is open or not
    if (open) {
        open = false;
        setHeight(70);
        setCenterY(55);
    }
    else {
        open = true;
        setCenterY(getCenterY() + (35*(options.size()-1)));
        setHeight(70 * options.size());
    }
}

void Dropdown::setCurrentOption(option option) {
    this->currentOption = option;
}

option Dropdown::getCurrentOption() const {
    return currentOption;
}

void Dropdown::setOptionColor(int index, color fill) {
    options[index].bg = fill;
}

void Dropdown::hover(int x, int y) {

    // determines which option is being hovered

    int index;

    int relativeY = y - getTopY();
    index = relativeY / 70;

    for (int i = 0; i < options.size(); i++) {
        if (i == index) {
            setOptionColor(i, {120.0/255.0, 120.0/255.0, 120.0/255.0});
        }
        else {
            setOptionColor(i, {0, 0, 0});
        }
    }

}

void Dropdown::press(int x, int y) {

    // determines which dropdown option is being pressed

    int index;

    int relativeY = y - getTopY();
    index = relativeY / 70;

    for (int i = 0; i < options.size(); i++) {
        if (i == index) {

            // clicking color
            setOptionColor(i, {90.0/255.0, 90.0/255.0, 90.0/255.0});

            // set currentOption
            setCurrentOption(options[i]);

            // swap new option into index 0
            option temp;
            temp = options[0];
            options[0] = options[i];
            options[i] = temp;

            toggle();
        }
        else {
            setOptionColor(i, {0, 0, 0});
        }
    }

}

void Dropdown::draw() const {

    // dropdown is not open, just draw first option
    if (!isOpen()) {

        // draw background box
        glBegin(GL_QUADS);
        glColor3f(options[0].bg.r, options[0].bg.g, options[0].bg.b);
        glVertex2f(getRightX(), getTopY());
        glVertex2f(getLeftX(), getTopY());
        glVertex2f(getLeftX(), getBottomY());
        glVertex2f(getRightX(), getBottomY());
        glEnd();

        // draw text
        glColor3f(1, 1, 1);
        glRasterPos2i(center.x - (options[0].offset * options[0].text.length()), center.y + 7);
        for (const char &letter : options[0].text) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

    }
    // drop down is open, draw all options
    else {
        for (int i = 0; i < options.size(); i++) {

            // calulates top, bottom, and center of each option's box
            int topY, bottomY, centerY;
            if (i == 0) {
                topY = getTopY();
                bottomY = getBottomY();
            }
            else {
                topY += 70;
            }
            centerY = getTopY() + ((getHeight() / options.size()) / 2) + (70*i) + 7;

            // draw background box
            glBegin(GL_QUADS);
            glColor3f(options[i].bg.r, options[i].bg.g, options[i].bg.b);
            glVertex2f(getRightX(), topY);
            glVertex2f(getLeftX(), topY);
            glVertex2f(getLeftX(), bottomY);
            glVertex2f(getRightX(), bottomY);
            glEnd();

            // draw text
            glColor3f(1, 1, 1);
            glRasterPos2i(center.x - (options[i].offset * options[i].text.length()), centerY);
            for (const char &letter : options[i].text) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }

        }
    }
}


