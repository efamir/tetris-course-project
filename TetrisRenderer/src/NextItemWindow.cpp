#include "../include/NextItemWindow.h"

NextItemWindow::NextItemWindow(Cursor & cursor, uint rows, uint cols, uint x, uint y)
: BlocksWindow(cursor, rows, cols, x, y) { }

void NextItemWindow::initDraw(uint x, uint y) {
    try {
        constexpr uint X_OFFSET = 2, Y_OFFSET = 1;
        _cursor.moveTo(x + X_OFFSET, y - Y_OFFSET);
        for (const char c: _windowText) {
            _cursor.fill(c, White, false);
        }
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in NextItemWindow::initDraw().");
    }
}
