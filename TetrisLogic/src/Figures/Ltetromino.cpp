#include "../../include/Figures/Ltetromino.h"

Ltetromino::Ltetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{1, 3}};
    pivot = 1;
}