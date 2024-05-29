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
    newTerminalAttributes.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newTerminalAttributes) == -1){
        throw std::runtime_error("Couldn't change Terminal attributes in InputReader::setFlags() method.\n");
    }
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void InputReader::resetFlags() {
    if (tcsetattr(STDIN_FILENO, TCSANOW, &storedTerminalAttributes) == -1){
        throw std::runtime_error("Couldn't change Terminal attributes in InputReader::resetFlags() method.\n");
    }
    fcntl(STDIN_FILENO, F_SETFL, 0);
}

char InputReader::readNextChar() {
    ssize_t bytes = read(STDIN_FILENO, &ch, 1);
    constexpr int NO_NEW_INPUT = -1;
    if (bytes == 0) return NO_NEW_INPUT;
    if (bytes == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return NO_NEW_INPUT;
        throw std::runtime_error("Something went wrong when reading in InputReader::readNextChar() method.\n");
    }
    return ch;
}
