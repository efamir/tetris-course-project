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

    void setFlags();
    void resetFlags();
    char readNextChar();
};


#endif //COURSEWORK_INPUTREADER_H
