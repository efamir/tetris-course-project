#include "../include/GameStatusDrawer.h"

GameStatusDrawer::GameStatusDrawer(Cursor & cursor) : _cursor(cursor) {}

void GameStatusDrawer::draw(std::wstring const& str, Color const& color) {
    constexpr uint START_DRAWING_AT_ROW_INDEX = 2;

    uint row = START_DRAWING_AT_ROW_INDEX;

    constexpr uint X_OFFSET = 1;
    _cursor.moveTo(X_OFFSET, row);

    for (wchar_t const ch: str) {
        if (ch == L'\n') {
            _cursor.moveTo(X_OFFSET, ++row);
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
