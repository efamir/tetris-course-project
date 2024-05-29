#ifndef TETRISLOGICMODULE_TETRISBASEFIGURE_H
#define TETRISLOGICMODULE_TETRISBASEFIGURE_H

#include <vector>
#include "../../../TetrisRenderer/include/TetrisRenderer.h"
#include <chrono>
#include <thread>
#include <random>
namespace FieldInfo {
    constexpr int FIELD_ROWS = 22;
    constexpr int FIELD_COLS = 10;
    constexpr int NEXT_FIGURE_FIELD_ROWS = 2;
    constexpr int NEXT_FIGURE_FIELD_COLS = 4;
    constexpr int ROW_COORDS_OFFSET = 2;
    constexpr int NEXT_FIGURE_COL_COORDS_OFFSET = 3;
    constexpr Color COLOR_FROM = Red;
    constexpr Color COLOR_TO = BCyan;
}

namespace DropDelay{
    constexpr int DELAY_MCRS = 20;
}

struct coords {
    unsigned int i;
    unsigned int j;
    coords(int i, int j);
};



namespace Random{
    extern std::mt19937 engine;
    extern std::uniform_int_distribution<int> randColor;
}

class Figure {
    Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS];
    const Color color;
    bool checkMoveLegalness(const std::vector<coords> &newCoords) const;
    TetrisRenderer &tetrisRenderer;

protected:
    int pivot;
    std::vector<coords> blockCoordsList;

public:
    Figure(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer, Color color = static_cast<Color>(Random::randColor(Random::engine)));
    void rotate();
    void moveLeft();
    void moveRight();
    bool moveDown();
    void draw();
    void drawAsNextFigure();
    void dropDown();
    void dropDown(unsigned int &score,int booster);
    virtual ~Figure();
};

#endif //TETRISLOGICMODULE_TETRISBASEFIGURE_H
