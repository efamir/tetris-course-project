#ifndef COURSEWORK_BLOCKSWINDOW_H
#define COURSEWORK_BLOCKSWINDOW_H

#include <string>
#include <stdexcept>
#include "Cursor.h"
#include "Color.h"

typedef unsigned int uint;

namespace BlocksWindowConsts {
    constexpr uint ROWS = 20, COLS = 10, X = 0, Y = 0;
}

class BlocksWindow {
protected:
    Cursor & _cursor;
    const uint _rows, _cols;
    const uint _x, _y;
public:
    BlocksWindow(Cursor & cursor,
                 uint rows = BlocksWindowConsts::ROWS,
                 uint cols = BlocksWindowConsts::COLS,
                 uint x = BlocksWindowConsts::X, uint y = BlocksWindowConsts::Y);
    void draw(uint rowI, uint colI, Color color = White, wchar_t const& ch = L'█');
    void clear();
};

#endif //COURSEWORK_BLOCKSWINDOW_H
