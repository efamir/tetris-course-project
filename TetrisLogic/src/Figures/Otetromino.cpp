#include "../../include/Figures/Otetromino.h"

Otetromino::Otetromino(Color (&field)[22][10]) : Figure(field) {
        blockCoordsList = {{0, 4},{0, 5},{1, 4},{1, 5}};

        std::vector<coords> state0 = {{0, 0},{0, 0},{0, 0},{0, 0}};

        setOfCoordsToChangeToGetState = {state0};
}