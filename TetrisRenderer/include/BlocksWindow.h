#ifndef COURSEWORK_BLOCKSWINDOW_H
#define COURSEWORK_BLOCKSWINDOW_H

#include <string>
#include <stdexcept>
#include "Cursor.h"
#include "Color.h"

typedef unsigned int uint;

class BlocksWindow {
protected:
    Cursor & _cursor;
    const uint _rows, _cols;
    const uint _x, _y;
public:
    BlocksWindow(Cursor & cursor, uint rows = 20, uint cols = 10, uint x = 0, uint y = 0);
    void draw(uint rowI, uint colI, Color color = White, wchar_t const& ch = L'█');
    void clear();
};

#endif //COURSEWORK_BLOCKSWINDOW_H
