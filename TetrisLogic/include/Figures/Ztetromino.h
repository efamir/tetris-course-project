#ifndef TETRIS_COURSE_PROJECT_ZTETROMINO_H
#define TETRIS_COURSE_PROJECT_ZTETROMINO_H

#endif //TETRIS_COURSE_PROJECT_ZTETROMINO_H

#include "TetrisBaseFigure.h"

class Ztetromino : public Figure {
public:
    Ztetromino(Color (&field)[22][10],TetrisRenderer tetrisRenderer);
};