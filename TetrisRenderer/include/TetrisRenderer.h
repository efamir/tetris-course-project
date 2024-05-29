#ifndef COURSEWORK_TETRISRENDERER_H
#define COURSEWORK_TETRISRENDERER_H

#include "Cursor.h"
#include "CursorManipulations.h"
#include "BackGround.h"
#include "BlocksWindow.h"
#include "NextItemWindow.h"
#include "Color.h"
#include "ScoreWindow.h"
#include "GameStatusDrawer.h"
#include <iostream>


class TetrisRenderer {
    Cursor _cursor;
    BackGround _bg;
    BlocksWindow _tw;
    NextItemWindow _niw;
    ScoreWindow _sw;
    GameStatusDrawer _gsd;

    void setCursorUnderTheGame();
public:
    TetrisRenderer();
    ~TetrisRenderer();

    // draws each window
    void initDraw();

    void drawTetrisWindowBlock(uint rowI, uint colI, Color color = White, wchar_t const& ch = DEFAULT_FILL_CHAR);
    void drawNextItemWindowBlock(uint rowI, uint colI, Color color = White, wchar_t const& ch = DEFAULT_FILL_CHAR);
    void setScore(uint score);
    void drawScore(Color scoreColor = White, Color bestScoreColor = White);
    void drawPause();
    void drawGameOver();
};


#endif //COURSEWORK_TETRISRENDERER_H