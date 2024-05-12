#include "../include/Cursor.h"

Cursor::Cursor(const uint xLength, const uint yLength, std::wostream & stream, const uint x, const uint y)
        : _xLen(xLength), _yLen(yLength), _stream(stream) {
    if (!xLength || !yLength) {
        throw std::invalid_argument("Invalid argument was passed to Cursor::Cursor(): "
                                    "X or Y length must be non-negative."); // TODO: make specified exception
    }
    if (x >= xLength || y >= yLength) {
        throw std::out_of_range("Out of range coordinate was passed to Cursor::Cursor(): "
                                "X/Y is/are >= to X/Y length"); // TODO: make specified exception
    }
    _x = x;
    _y = y;
}

void Cursor::moveTo(const uint x, const uint y) {
    if (x >= _xLen || y >= _yLen) {
        throw std::out_of_range("Out of range value was passed to Cursor::moveTo() method: "
                                "X/Y is/are >= to X/Y length"); // TODO: change exception
    }
    int xDiff = x - _x;
    int yDiff = y - _y;

    if (xDiff > 0) {
        ANSICursorRight(_stream, xDiff);
    } else if (xDiff < 0) {
        ANSICursorLeft(_stream, -xDiff);
    }

    if (yDiff > 0) {
        ANSICursorDown(_stream, yDiff);
    } else if (yDiff < 0) {
        ANSICursorUp(_stream, -yDiff);
    }

    _x = x;
    _y = y;
}

void Cursor::fill(wchar_t const& c, Color const color, bool resetPos) {
    _stream << ColorANSI.at(color);
    _stream << c;
    if (resetPos) ANSICursorLeft(_stream, 1);
    else ++_x;
}
