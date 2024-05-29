#ifndef COURSEWORK_INPUTREADER_H
#define COURSEWORK_INPUTREADER_H

#include "termios.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdexcept"

class InputReader {
    struct termios storedTerminalAttributes;
    char ch;
public:
    InputReader();
    ~InputReader();

    // sets input flags for tetris game
    void setFlags();

    // resets all the flags to initial status
    void resetFlags();

    // returns the read char is found, else returns -1
    char readNextChar();
};


#endif //COURSEWORK_INPUTREADER_H
