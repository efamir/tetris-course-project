#ifndef TETRIS_COURSE_PROJECT_TTETROMINO_H
#define TETRIS_COURSE_PROJECT_TTETROMINO_H
#include "TetrisBaseFigure.h"

class Ttetromino : public Figure {
public:
    Ttetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};

#endif //TETRIS_COURSE_PROJECT_TTETROMINO_H
