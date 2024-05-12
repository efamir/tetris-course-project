#ifndef TETRIS_COURSE_PROJECT_JTETROMINO_H
#define TETRIS_COURSE_PROJECT_JTETROMINO_H

#endif //TETRIS_COURSE_PROJECT_JTETROMINO_H

#include "TetrisBaseFigure.h"

class Jtetromino : public Figure {
public:
    Jtetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer);
};