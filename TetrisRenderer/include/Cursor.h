#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include "CursorManipulations.h"
#include <iostream>
#include <string>
#include <map>
#include "Color.h"
#include <stdexcept>

typedef unsigned int uint;

class Cursor {
    uint _x, _y;
    const uint _xLen, _yLen;
    std::ostream & _stream;
public:
    Cursor(const uint xLength, const uint yLength, std::ostream & stream, const uint x = 0, const uint y = 0);

    void moveTo(const uint x = 0, const uint y = 0);

    void fill(std::string const& c, Color const color = White, bool resetPos = true);

    void fill(char const& c, Color const color = White, bool resetPos = true);
};

#endif //COURSEWORK_CURSOR_H
