#include "../../include/Figures/Jtetromino.h"

Jtetromino::Jtetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{1, 5}};
    pivot = 1;
}