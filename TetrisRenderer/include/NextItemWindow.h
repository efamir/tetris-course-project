#ifndef COURSEWORK_NEXTITEMWINDOW_H
#define COURSEWORK_NEXTITEMWINDOW_H

#include "BlocksWindow.h"
#include "Color.h"
#include <string>

namespace NextItemWindowConsts {
    constexpr uint ROWS = 2, COLS = 4, X = 22, Y = 6;
}

class NextItemWindow : public BlocksWindow {
    const std::string _windowText = "NEXT";
public:
    NextItemWindow(Cursor & cursor,
                   uint rows = NextItemWindowConsts::ROWS,
                   uint cols = NextItemWindowConsts::COLS,
                   uint x = NextItemWindowConsts::X,
                   uint y = NextItemWindowConsts::Y);
    void initDraw(uint x = NextItemWindowConsts::X, uint y = NextItemWindowConsts::Y);
};


#endif //COURSEWORK_NEXTITEMWINDOW_H
