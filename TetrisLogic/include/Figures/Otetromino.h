#ifndef TETRIS_COURSE_PROJECT_OTETROMINO_H
#define TETRIS_COURSE_PROJECT_OTETROMINO_H


#include "TetrisBaseFigure.h"

class Otetromino : public Figure {
public:
    Otetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};
#endif //TETRIS_COURSE_PROJECT_OTETROMINO_H










