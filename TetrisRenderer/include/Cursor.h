#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include "CursorManipulations.h"
#include <iostream>
#include <string>
#include <map>
#include "Color.h"
#include <stdexcept>

typedef unsigned int uint;

constexpr wchar_t DEFAULT_FILL_CHAR = L'█';

class Cursor {
    uint _x, _y; // cursor coordinates
    const uint _xLen, _yLen; // x/y axis length
    std::wostream & _stream; // output stream
public:
    Cursor(const uint xLength, const uint yLength, std::wostream & stream, const uint x = 0, const uint y = 0);

    // moves cursor to passed coordinates
    void moveTo(const uint x = 0, const uint y = 0);

    // fills the char with passed color/char under which cursor is set
    void fill(wchar_t const& c = DEFAULT_FILL_CHAR, Color const color = White, bool resetPos = true);
};

#endif //COURSEWORK_CURSOR_H
