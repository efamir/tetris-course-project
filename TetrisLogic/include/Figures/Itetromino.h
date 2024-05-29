#ifndef TETRIS_COURSE_PROJECT_I_TETRAMINO_H
#define TETRIS_COURSE_PROJECT_I_TETRAMINO_H

#include "TetrisBaseFigure.h"

class Itetromino : public Figure {
public:
    Itetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};

#endif //TETRIS_COURSE_PROJECT_I_TETRAMINO_H
