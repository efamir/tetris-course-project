#ifndef COURSEWORK_TETRISRENDERER_H
#define COURSEWORK_TETRISRENDERER_H

#include "Cursor.h"
#include "CursorManipulations.h"
#include "BackGround.h"
#include "BlocksWindow.h"
#include "NextItemWindow.h"
#include "Color.h"
#include "ScoreWindow.h"
#include <iostream>


class TetrisRenderer {
    Cursor _cursor;
    BackGround _bg;
    BlocksWindow _tw;
    NextItemWindow _niw;
    ScoreWindow _sw;

    void setCursorUnderTheGame();
public:
    TetrisRenderer();
    ~TetrisRenderer();

    void initDraw();
    void drawTetrisWindowBlock(uint rowI, uint colI, Color color = White, std::string const& s = "█");
    void drawNextItemWindowBlock(uint rowI, uint colI, Color color = White, std::string const& s = "█");
    void setScore(uint score);
    void drawScore(Color scoreColor = White, Color bestScoreColor = White);
};


#endif //COURSEWORK_TETRISRENDERER_H