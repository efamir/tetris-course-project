#ifndef TETRIS_COURSE_PROJECT_LTETROMINO_H
#define TETRIS_COURSE_PROJECT_LTETROMINO_H

#include "TetrisBaseFigure.h"

class Ltetromino : public Figure {
public:
    Ltetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};

#endif //TETRIS_COURSE_PROJECT_LTETROMINO_H
