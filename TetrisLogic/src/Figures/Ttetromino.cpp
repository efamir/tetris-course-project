#include "../../include/Figures/Ttetromino.h"

Ttetromino::Ttetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{1, 4}};

    pivot = 1;
}