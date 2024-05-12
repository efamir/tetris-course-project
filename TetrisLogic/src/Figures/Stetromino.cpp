#include "../../include/Figures/Stetromino.h"

Stetromino::Stetromino(Color (&field)[22][10],TetrisRenderer tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{1, 3},{1, 4},{0, 4},{0, 5}};

    pivot = 2;

    /*std::vector<coords> state0 = {{1,-1},{0,0},{-1,1},{-2,2}};
    std::vector<coords> state1 = {{-1,1},{0,0},{1,-1},{2,-2}};

    setOfCoordsToChangeToGetState = {state0,state1};*/
}