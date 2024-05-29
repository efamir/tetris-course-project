#include "../../include/Figures/Stetromino.h"

Stetromino::Stetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{1, 3},{1, 4},{0, 4},{0, 5}};
    pivot = 2;
}