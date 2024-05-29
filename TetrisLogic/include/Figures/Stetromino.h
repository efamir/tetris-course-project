#ifndef TETRIS_COURSE_PROJECT_STETROMINO_H
#define TETRIS_COURSE_PROJECT_STETROMINO_H


#include "TetrisBaseFigure.h"

class Stetromino : public Figure {
public:
    Stetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};
#endif //TETRIS_COURSE_PROJECT_STETROMINO_H
