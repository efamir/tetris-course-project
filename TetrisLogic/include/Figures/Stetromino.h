#ifndef TETRIS_COURSE_PROJECT_STETROMINO_H
#define TETRIS_COURSE_PROJECT_STETROMINO_H

#endif //TETRIS_COURSE_PROJECT_STETROMINO_H

#include "TetrisBaseFigure.h"

class Stetromino : public Figure {
public:
    Stetromino(Color (&field)[22][10],TetrisRenderer tetrisRenderer);
};