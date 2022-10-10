#ifndef ABSTRACT_TYPES_H
#define ABSTRACT_TYPES_H

// General Dimension class for widgets/console window...
struct Dimension {
    Dimension() {}

    Dimension(int length, int width) {
        this->length_ = length;
        this->width_ = width;
    }

    Dimension(const Dimension& dim) {
        this->length_ = dim.length_;
        this->width_ = dim.width_;
    }

    int length_;
    int width_;
};

// Widgets Rendering Coordinates...
struct Coordinate {

    Coordinate() {
        x_ = 0;
        y_ = 0;
    }

    Coordinate(int x, int y) {
        this->x_ = x;
        this->y_ = y;
    }

    Coordinate(const Coordinate& coord) {
        this->x_ = coord.x_;
        this->y_ = coord.y_;
    }

    int x_;
    int y_;
};

// MenuOption selection theme...
struct Theme {
    Theme() {}

    Theme(int background, int highlight) {
        background_ = background;
        highlight_ = highlight;
    }

    int background_;
    int highlight_;
};


enum INPUT_KEYS { UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80 };

struct InputKeyEvent {
    InputKeyEvent() {}

    InputKeyEvent(INPUT_KEYS key_one, INPUT_KEYS key_two) {
        this->key_one_ = key_one;
        this->key_two_ = key_two;
    }

    INPUT_KEYS key_one_, key_two_;
};

#endif
