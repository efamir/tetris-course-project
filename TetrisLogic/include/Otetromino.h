#ifndef TETRIS_COURSE_PROJECT_OTETROMINO_H
#define TETRIS_COURSE_PROJECT_OTETROMINO_H

#endif //TETRIS_COURSE_PROJECT_OTETROMINO_H

#include "TetrisBaseFigure.h"

class Otetromino : public Figure {
public:
    Otetromino(Color (&field)[22][10]);
};

Otetromino::Otetromino(Color (&field)[22][10]) : Figure(field) {
    blockCoordsList = {{0, 4},{0, 5},{1, 4},{1, 5}};

    std::vector<coords> state0 = {{0, 0},{0, 0},{0, 0},{0, 0}};

    setOfCoordsToChangeToGetState = {state0};
}










