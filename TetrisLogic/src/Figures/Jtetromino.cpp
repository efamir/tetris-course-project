#include "../../include/Figures/Jtetromino.h"

Jtetromino::Jtetromino(Color (&field)[22][10],TetrisRenderer &tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{1, 5}};
    pivot = 1;
}