#ifndef COURSEWORK_BACKGROUND_H
#define COURSEWORK_BACKGROUND_H

#include "CursorManipulations.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "Color.h"

typedef unsigned int uint;

struct BackGroundColors { // can be rewritten to wide chars
    Color interWindowColor;
    Color tetrisBackgroundColor;
    Color nextPieceBackgroundColor;
    Color scoreWindowBackgroundColor;
};

class BackGround {
    const uint cols = 33, rows = 22;
    const uint tetrisWindowWidth = 20, secondWindowWidth = 10;
    const uint scoreWindowRows = 4, nextItemWindowRows = 4;
    BackGroundColors _colors;
    void drawSolidLine(std::ostream & stream, uint times = 1) const;
    void drawWithTetrisBg(std::ostream & stream, uint times = 1) const;
    void drawWithTwoBg(std::ostream & stream, Color secondBgColor, uint times = 1) const;
public:
    BackGround(BackGroundColors const& colors);

    void draw(std::ostream & stream) const;
};

#endif //COURSEWORK_BACKGROUND_H
