#include "../include/CursorManipulations.h"

void ANSICursorUp(std::ostream & stream, int n, bool moveStartLine) {
    if (moveStartLine) stream << '\r';
    stream << "\x1b[" << n << 'A';
}

void ANSICursorDown(std::ostream & stream, int n, bool moveStartLine) {
    if (moveStartLine) stream << '\r';
    stream << "\x1b[" << n << 'B';
}

void ANSICursorLeft(std::ostream &stream, int n) {
    stream << "\x1b[" << n << 'D';
}

void ANSICursorRight(std::ostream &stream, int n) {
    stream << "\x1b[" << n << 'C';
}
