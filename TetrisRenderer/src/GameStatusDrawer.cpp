#include "../include/GameStatusDrawer.h"
#include <fstream>

GameStatusDrawer::GameStatusDrawer(Cursor & cursor) : _cursor(cursor) {}

void GameStatusDrawer::drawPause() {
    std::wifstream pauseFile("../TetrisRenderer/pause.txt"); // todo remove hardcode
    if (!pauseFile.is_open()) {
        throw std::runtime_error("Couldn't open pause.txt file.");
    }
    pauseFile >> std::noskipws;

    uint row = 2;
    _cursor.moveTo(1, row);

    wchar_t ch;
    for (;pauseFile.get(ch);) {
        if (ch == L'\n') {
            _cursor.moveTo(1, ++row);
            continue;
        }
        if (ch == L'\r') continue;
        _cursor.fill(ch, Red, false);
    }
}

void GameStatusDrawer::drawGameOver() {
    std::wifstream pauseFile("../TetrisRenderer/gameover.txt"); // todo remove hardcode
    if (!pauseFile.is_open()) {
        throw std::runtime_error("Couldn't open gameover.txt file.");
    }
    pauseFile >> std::noskipws;

    uint row = 2;
    _cursor.moveTo(1, row);

    wchar_t ch;
    for (;pauseFile.get(ch);) {
        if (ch == L'\n') {
            _cursor.moveTo(1, ++row);
            continue;
        }
        if (ch == L'\r') continue;
        _cursor.fill(ch, Magenta, false);
    }
}
