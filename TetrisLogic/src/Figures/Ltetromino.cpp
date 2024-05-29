#include "../../include/Figures/Ltetromino.h"

Ltetromino::Ltetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{1, 3}};
    pivot = 1;
}