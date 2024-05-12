#include "../include/CursorManipulations.h"

void ANSICursorUp(std::wostream & stream, int n, bool moveStartLine) {
    if (moveStartLine) stream << '\r';
    stream << "\x1b[" << n << 'A';
}

void ANSICursorDown(std::wostream & stream, int n, bool moveStartLine) {
    if (moveStartLine) stream << '\r';
    stream << "\x1b[" << n << 'B';
}

void ANSICursorLeft(std::wostream &stream, int n) {
    stream << "\x1b[" << n << 'D';
}

void ANSICursorRight(std::wostream &stream, int n) {
    stream << "\x1b[" << n << 'C';
}
