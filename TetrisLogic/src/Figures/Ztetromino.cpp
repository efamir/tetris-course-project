#include "../../include/Figures/Ztetromino.h"

Ztetromino::Ztetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{1, 4},{1, 5}};

    pivot = 2;

}