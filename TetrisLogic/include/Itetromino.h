#ifndef TETRIS_COURSE_PROJECT_I_TETRAMINO_H
#define TETRIS_COURSE_PROJECT_I_TETRAMINO_H

#endif //TETRIS_COURSE_PROJECT_I_TETRAMINO_H


#include "TetrisBaseFigure.h"

class Itetromino : public Figure {
public:
    Itetromino(Color (&field)[22][10]);
};

Itetromino::Itetromino(Color (&field)[22][10]) : Figure(field) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{0, 6}};

    std::vector<coords> state0 = {{1,-1},{0,0},{-1,1},{-2,2}};
    std::vector<coords> state1 = {{-1,1},{0,0},{1,-1},{2,-2}};

    setOfCoordsToChangeToGetState = {state0,state1};

}