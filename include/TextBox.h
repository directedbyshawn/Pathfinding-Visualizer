#ifndef PATHFINDING_TEXTBOX_H
#define PATHFINDING_TEXTBOX_H

#include "Entity.h"
#include <string>

class TextBox : public Entity {

protected:

    std::string text;
    color stringColor;
    double offset;

public:


    TextBox();
    explicit TextBox(std::string text);
    TextBox(std::string text, color stringColor);
    TextBox(std::string text, color stringColor, point center, color fill);

    virtual ~TextBox() = default;

    void toggleButton();
    void setText(std::string text);
    std::string getText() const;
    void setOffset(double offset);
    double getOffset() const;
    void move(int deltaX, int deltaY);
    void draw() const override;

};

#endif //PATHFINDING_TEXTBOX_H
