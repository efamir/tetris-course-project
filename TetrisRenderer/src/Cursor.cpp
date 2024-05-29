#include "../include/Cursor.h"

Cursor::Cursor(const uint xLength, const uint yLength, std::wostream & stream, const uint x, const uint y)
        : _xLen(xLength), _yLen(yLength), _stream(stream) {
    if (xLength == 0) {
        throw std::invalid_argument("Invalid argument was passed to Cursor::Cursor(): "
                                    "xLength must not equal 0.");
    }
    if (yLength == 0) {
        throw std::invalid_argument("Invalid argument was passed to Cursor::Cursor(): "
                                    "yLength must not equal 0.");
    }
    if (x >= xLength) {
        throw std::out_of_range("Out of range coordinate was passed to Cursor::Cursor(): "
                                "x can't be greater or equal to xLength: x = "
                                + std::to_string(x) + "; xLength = "
                                + std::to_string(xLength));
    }
    if (y >= yLength) {
        throw std::out_of_range("Out of range coordinate was passed to Cursor::Cursor(): "
                                "y can't be greater or equal to yLength: y = "
                                + std::to_string(y) + "; yLength = "
                                + std::to_string(yLength));
    }
    _x = x;
    _y = y;
}

void Cursor::moveTo(const uint x, const uint y) {
    if (x >= _xLen) {
        throw std::out_of_range("Out of range value was passed to Cursor::moveTo() method: "
                                "x can't be greater or equal to xLength: x = "
                                + std::to_string(x) + "; xLength = "
                                + std::to_string(_xLen));
    }

    if (y >= _yLen) {
        throw std::out_of_range("Out of range value was passed to Cursor::moveTo() method: "
                                "y can't be greater or equal to yLength: y = "
                                + std::to_string(y) + "; yLength = "
                                + std::to_string(_yLen));
    }

    // calculate n of chars to move by x/y
    int xDiff = x - _x;
    int yDiff = y - _y;

    // checks the direction and moves by x-axis
    if (xDiff > 0) {
        ANSICursorRight(_stream, xDiff);
    } else if (xDiff < 0) {
        ANSICursorLeft(_stream, -xDiff);
    }

    // checks the direction and moves by y-axis
    if (yDiff > 0) {
        ANSICursorDown(_stream, yDiff);
    } else if (yDiff < 0) {
        ANSICursorUp(_stream, -yDiff);
    }

    // set new coordinates values
    _x = x;
    _y = y;
}

void Cursor::fill(wchar_t const& c, Color const color, bool resetPos) {
    _stream << ColorANSI::get(color);
    _stream << c;

    // if resetPos sets cursor back to original coordinates
    if (resetPos) ANSICursorLeft(_stream, 1);
    else ++_x;
}
