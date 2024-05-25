#include "../include/GameStatusDrawer.h"

GameStatusDrawer::GameStatusDrawer(Cursor & cursor) : _cursor(cursor) {}

void GameStatusDrawer::draw(const std::wstring &str, Color const& color) {
    uint row = 2;
    _cursor.moveTo(1, row);

    for (wchar_t const ch: str) {
        if (ch == L'\n') {
            _cursor.moveTo(1, ++row);
            continue;
        }
        _cursor.fill(ch, color, false);
    }
}

void GameStatusDrawer::drawPause() {
    std::wstring const pause =
            L"█▀█ ▄▀█ █░█ █▀ █▀▀\n"
             "█▀▀ █▀█ █▄█ ▄█ ██▄\n"
             "\n"
             "press p to continue";

    draw(pause, Magenta);
}

void GameStatusDrawer::drawGameOver() {
    std::wstring const gameOver =
            L"█▀▀ ▄▀█ █▀▄▀█ █▀▀\n"
             "█▄█ █▀█ █░▀░█ ██▄\n"
             "\n"
             " █▀█ █░█ █▀▀ █▀█\n"
             " █▄█ ▀▄▀ ██▄ █▀▄\n"
             " \n"
             " press q to quit\n"
             " or r to restart";

    draw(gameOver, BMagenta);
}
