#include "../../include/Figures/Otetromino.h"

Otetromino::Otetromino(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
        blockCoordsList = {{0, 4},{0, 5},{1, 4},{1, 5}};
        pivot = -1;
}