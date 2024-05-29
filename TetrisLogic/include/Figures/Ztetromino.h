#ifndef TETRIS_COURSE_PROJECT_ZTETROMINO_H
#define TETRIS_COURSE_PROJECT_ZTETROMINO_H

#include "TetrisBaseFigure.h"

class Ztetromino : public Figure {
public:
    Ztetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};
#endif //TETRIS_COURSE_PROJECT_ZTETROMINO_H
