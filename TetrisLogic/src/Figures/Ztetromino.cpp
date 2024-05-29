#include "../../include/Figures/Ztetromino.h"

Ztetromino::Ztetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{1, 4},{1, 5}};
    pivot = 2;
}