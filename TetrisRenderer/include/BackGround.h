#ifndef COURSEWORK_BACKGROUND_H
#define COURSEWORK_BACKGROUND_H

#include "CursorManipulations.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "Color.h"

typedef unsigned int uint;

struct BackGroundColors {
    Color interWindowColor;
    Color tetrisBackgroundColor;
    Color nextPieceBackgroundColor;
    Color scoreWindowBackgroundColor;
};

class BackGround {
    static constexpr uint COLS = 33, ROWS = 22;
    static constexpr uint TETRIS_WINDOW_WIDTH = 20, SECOND_WINDOW_WIDTH = 10;
    static constexpr uint SCORE_WINDOW_ROWS = 4, NEXT_ITEM_WINDOW_ROWS = 4;
    BackGroundColors _colors;
    void drawSolidLine(std::wostream & stream, wchar_t const& ch, const uint times = 1) const;
    void drawWithTetrisBg(std::wostream & stream, wchar_t const& ch, const uint times = 1) const;
    void drawWithTwoBg(std::wostream & stream, wchar_t const& ch, Color secondBgColor, const uint times = 1) const;
public:
    BackGround(BackGroundColors const& colors);

    void draw(std::wostream & stream, wchar_t const& ch = L'█') const;
};

#endif //COURSEWORK_BACKGROUND_H
