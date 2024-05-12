#include "../include/BlocksWindow.h"

BlocksWindow::BlocksWindow(Cursor & cursor, uint rows, uint cols, uint x, uint y)
: _cursor(cursor), _rows(rows), _cols(cols), _x(x), _y(y) {
    if (!cols || !rows) {
        throw std::invalid_argument("Invalid argument was passed to BlocksWindow::BlocksWindow(): "
                                    "Cols or Rows number must be non-negative."); // TODO: change exception
    }
}

void BlocksWindow::draw(uint rowI, uint colI, Color color, wchar_t const& ch) {
    if (rowI >= _rows || colI >= _cols) {
        throw std::out_of_range("Out of range value was passed to BlocksWindow method: "
                                "rowI/colI is/are >= to rows/cols length"); // TODO: change exception
    }

    try {
        _cursor.moveTo(_x + colI * 2, _y + rowI);
        _cursor.fill(ch, color, false);
        _cursor.fill(ch, color);
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in BlocksWindow::draw().");
    }
}

void BlocksWindow::clear() {
    for (uint r = 0; r < _rows; ++r) {
        for (uint c = 0; c < _cols; ++c) {
            try {
                draw(r, c, Black);
            } catch (std::exception const& e) {
                throw e;
            }
        }
    }
}
