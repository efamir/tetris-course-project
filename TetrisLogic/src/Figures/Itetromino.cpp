#include "../../include/Figures/Itetromino.h"

Itetromino::Itetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{0, 6}};

    pivot = 1;

}