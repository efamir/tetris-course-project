#include "../../include/Figures/Ztetromino.h"

Ztetromino::Ztetromino(Color (&field)[22][10],TetrisRenderer tetrisRenderer) : Figure(field,tetrisRenderer) {
    blockCoordsList = {{0, 3},{0, 4},{1, 4},{1, 5}};

    pivot = 2;

    /*std::vector<coords> state0 = {{1,-1},{0,0},{-1,1},{-2,2}};
    std::vector<coords> state1 = {{-1,1},{0,0},{1,-1},{2,-2}};

    setOfCoordsToChangeToGetState = {state0,state1};*/
}