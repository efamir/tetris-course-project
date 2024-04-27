#include "../include/NextItemWindow.h"

NextItemWindow::NextItemWindow(Cursor &cursor, uint rows, uint cols, uint x, uint y)
: BlocksWindow(cursor, rows, cols, x, y) { }

void NextItemWindow::initDraw(uint x, uint y) {
    try {
        _cursor.moveTo(x + 2, y - 1);
        for (char c: _windowText) {
            _cursor.fill(c, White, false);
        }
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in NextItemWindow::initDraw().");
    }
}
