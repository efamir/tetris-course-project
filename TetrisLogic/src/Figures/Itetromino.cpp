#include "../../include/Figures/Itetromino.h"

Itetromino::Itetromino(Color (&field)[22][10]) : Figure(field) {
    blockCoordsList = {{0, 3},{0, 4},{0, 5},{0, 6}};

    std::vector<coords> state0 = {{1,-1},{0,0},{-1,1},{-2,2}};
    std::vector<coords> state1 = {{-1,1},{0,0},{1,-1},{2,-2}};

    setOfCoordsToChangeToGetState = {state0,state1};
}