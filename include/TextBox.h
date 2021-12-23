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

    /**
     * Initializes text box with text as "Default text"
     */
    TextBox();

    /**
     * Initializes text box with custom text
     *
     * @param text custom text
     */
    explicit TextBox(std::string text);

    /**
     * Initializes text box with custom text and custom color
     *
     * @param text custom text
     * @param stringColor text color
     */
    TextBox(std::string text, color stringColor);

    /**
     * Initializes text box with custom text, color, center, fill
     *
     * @param text custom text
     * @param stringColor text color
     * @param center center point of box
     * @param fill background color
     */
    TextBox(std::string text, color stringColor, point center, color fill);

    virtual ~TextBox() = default;

    /**
     * Set text of textbox
     *
     * @param text text
     */
    void setText(std::string text);

    /**
     * Get text of textbox
     *
     * @return text
     */
    std::string getText() const;

    /**
     * The only way to center text when bit mapping is to find the right
     * offset value, often it is between 4.0 and 5.5 for short strings
     *
     * @param offset offset value for mapping text
     */
    void setOffset(double offset);

    /**
     * The only way to center text when bit mapping is to find the right
     * offset value, often it is between 4.0 and 5.5 for short strings
     *
     * @return offset value for mapping text
     */
    double getOffset() const;

    /**
     * Moves text box and text
     *
     * @param deltaX change in x value
     * @param deltaY change in y value
     */
    void move(int deltaX, int deltaY);

    /**
     * Draw text box and text to display
     */
    void draw() const override;

};

#endif //PATHFINDING_TEXTBOX_H
