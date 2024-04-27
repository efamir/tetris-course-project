#ifndef COURSEWORK_NEXTITEMWINDOW_H
#define COURSEWORK_NEXTITEMWINDOW_H

#include "BlocksWindow.h"
#include "Color.h"
#include <string>


class NextItemWindow : public BlocksWindow {
    std::string _windowText = "NEXT";
public:
    NextItemWindow(Cursor & cursor, uint rows = 2, uint cols = 4, uint x = 22, uint y = 6);
    void initDraw(uint x = 22, uint y = 6);
};


#endif //COURSEWORK_NEXTITEMWINDOW_H
