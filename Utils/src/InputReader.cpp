#include "../include/InputReader.h"

InputReader::InputReader() {
    if (tcgetattr(STDIN_FILENO, &storedTerminalAttributes) == -1){
        throw std::runtime_error("Couldn't get terminal attributes in InputReader::InputReader() constructor.\n");
    }
}

InputReader::~InputReader() {
    try {
        resetFlags();
    } catch (...) { }
}

void InputReader::setFlags() {
    struct termios newTerminalAttributes = storedTerminalAttributes;

    // non-echo and non-canon mask
    newTerminalAttributes.c_lflag &= ~(ECHO | ICANON);

    // sets the mask
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newTerminalAttributes) == -1) {
        throw std::runtime_error("Couldn't change Terminal attributes in InputReader::setFlags() method.\n");
    }

    // non-block mode
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void InputReader::resetFlags() {
    // set the initial attributes
    if (tcsetattr(STDIN_FILENO, TCSANOW, &storedTerminalAttributes) == -1) {
        throw std::runtime_error("Couldn't change Terminal attributes in InputReader::resetFlags() method.\n");
    }
    fcntl(STDIN_FILENO, F_SETFL, 0);
}

char InputReader::readNextChar() {
    // read 1 byte from buffer
    ssize_t bytes = read(STDIN_FILENO, &ch, 1);

    constexpr int NO_NEW_INPUT = -1;

    if (bytes == 0) return NO_NEW_INPUT;

    if (bytes == -1) {
        // checks if everything fine
        if (errno == EAGAIN || errno == EWOULDBLOCK) return NO_NEW_INPUT;

        throw std::runtime_error("Something went wrong when reading in InputReader::readNextChar() method.\n");
    }

    return ch;
}
