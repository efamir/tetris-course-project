#ifndef TETRIS_COURSE_PROJECT_JTETROMINO_H
#define TETRIS_COURSE_PROJECT_JTETROMINO_H


#include "TetrisBaseFigure.h"

class Jtetromino : public Figure {
public:
    Jtetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer);
};
#endif //TETRIS_COURSE_PROJECT_JTETROMINO_H
