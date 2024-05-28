#ifndef TETRISLOGICMODULE_TETRISBASEFIGURE_H
#define TETRISLOGICMODULE_TETRISBASEFIGURE_H



#include <vector>
#include "../../../TetrisRenderer/include/TetrisRenderer.h"
#include <chrono>
#include <thread>
#include <random>

struct coords {
    unsigned int i;
    unsigned int j;
    coords(int i, int j);
};

extern  std::mt19937 engine;
extern  std::uniform_int_distribution<int> randColor;

class Figure {
    Color (&field)[22][10];
    const Color color;
    bool checkMoveLegalness(std::vector<coords> newCoords);
    TetrisRenderer &tetrisRenderer;

protected:
    int pivot;
    std::vector<coords> blockCoordsList;

public:
    Figure(Color (&field)[22][10],TetrisRenderer &tetrisRenderer, Color color = static_cast<Color>(randColor(engine)));
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
