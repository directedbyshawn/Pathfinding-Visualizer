#ifndef PATHFINDING_DROPDOWN_H
#define PATHFINDING_DROPDOWN_H

#include "Entity.h"
#include <vector>
#include <string>

struct option {

    std::string text;
    double offset;
    color bg;

    option();
    option(std::string text, double offset);

};

class Dropdown : public Entity {

private:

    std::vector<option> options;
    option currentOption;
    bool open;

public:

    Dropdown();

    virtual ~Dropdown() = default;

    void addOption(option option);
    std::vector<option> getOptions() const;
    bool isOpen() const;
    void setOptionColor(int index, color fill);
    void toggle();
    void setCurrentOption(option);
    option getCurrentOption() const;
    void hover(int x, int y);
    void press(int x, int y);
    void draw() const override;

};

#endif //PATHFINDING_DROPDOWN_H
