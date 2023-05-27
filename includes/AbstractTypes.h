/*
* Simple POCO classes
*/

#ifndef ABSTRACT_TYPES_H
#define ABSTRACT_TYPES_H
#include "AbstractTypes.h"
#include "..\lib\includes\vain_engine.h"

/* 
* General Dimension class for widgets
*/
struct Dimension {
    
    Dimension() {}

    Dimension(int length, int width) {
        this->length_ = length;
        this->width_  = width;
    }

    Dimension(const Dimension& dimension) {
        this->length_ = dimension.length_;
        this->width_  = dimension.width_;
    }

    int length_;
    int width_;
};

/* 
* Widgets Rendering Coordinates
*/
struct Coordinate {

    Coordinate() {}

    Coordinate(int x, int y) {
        this->x_ = x;
        this->y_ = y;
    }

    Coordinate(const Coordinate& coordinate) {
        this->x_ = coordinate.x_;
        this->y_ = coordinate.y_;
    }

    int x_;
    int y_;
};


/*
* MenuOption selection theme...
* Note: To achieve colors
* we have to use Hex-values 
* because winapi uses hex-values
* at operating system level api calls
* so in order to use hex values
* we can use int, std::uint8_t, 
* std::uint32_t datatypes.
* We will be using int datatype.
*/
typedef eng::Color::HexaDecimalColours Color;
struct Theme {
    
    Theme() {}
    
    Theme(Color background, Color highlight) {
        background_ = background;
        highlight_  = highlight;
    }
    
    Color background_;
    Color highlight_;
};


enum Keys { 
    UP    = 72,  // ascii code for up-arrow key
    LEFT  = 75,  // ascii code for left-arrow key
    RIGHT = 77,  // ascii code for right-arrow key
    DOWN  = 80   // ascii code for down-arrow key
};



/*
* For input event handling 
*/
struct InputKey {
    
    InputKey() {}

    InputKey(Keys key_one, Keys key_two) {
        this->key_one_ = key_one;
        this->key_two_ = key_two;
    }

    Keys key_one_, key_two_;
};

#endif
