#ifndef TETRISLOGICMODULE_TETRISBASEFIGURE_H
#define TETRISLOGICMODULE_TETRISBASEFIGURE_H

#endif //TETRISLOGICMODULE_TETRISBASEFIGURE_H


#include <vector>
#include "../../TetrisRenderer/include/TetrisRenderer.h"
#include <chrono>
#include <thread>
#include <random>

struct coords {
    unsigned int i;
    unsigned int j;

    coords(int i, int j) {
        this->i = i;
        this->j = j;
    }
};

typedef std::vector<std::vector<coords>> states;//

std::random_device rd;
std::mt19937 engine{rd()};
std::uniform_int_distribution<int> randColor{2, 14 - 1};

class Figure {
    Color (&field)[22][10];
    const Color color;
    unsigned int currentState;

    bool checkMoveLegalness(std::vector<coords> newCoords);

protected:
    states setOfCoordsToChangeToGetState;
    std::vector<coords> blockCoordsList;

public:
    static TetrisRenderer tetrisRenderer;//здається я виніс це в паблік щоб використовувати в тестах //todo повернути назад в private

    Figure(Color (&field)[22][10],
           Color color = static_cast<Color>(randColor(engine))) : field(field), color(color) {
        currentState = 0; //не надається можливість обрати випадкову початкову форму через можливе
        // винекнення проблем(або бо так у стандартному тетрісі(поле наступної фігури всього 2 блоки у висоту))
        //blockCoordsList = blockCrdsLst;
        for (coords ij: blockCoordsList) {
            field[ij.i][ij.j] = color;
        }

    }

    void rotate();

    void moveLeft();

    void moveRight();

    bool moveDown();

    void draw();
};


TetrisRenderer Figure::tetrisRenderer;

void Figure::rotate() {
    std::vector<coords> temp(blockCoordsList);
    int nextState;

    nextState = (currentState + 1) % setOfCoordsToChangeToGetState.size();

    int i = 0;
    for (coords &coord: temp) {
        coord.i += setOfCoordsToChangeToGetState[nextState][i].i;
        coord.j += setOfCoordsToChangeToGetState[nextState][i].j;
        i++;
    }

    if (!checkMoveLegalness(temp)) { return; }

    currentState = (currentState + 1) % setOfCoordsToChangeToGetState.size();

    for (coords &coord: blockCoordsList) {
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) {
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp);
    draw();
    return;
}

bool Figure::moveDown() {
    std::vector<coords> temp(blockCoordsList);

    for (coords &coord: temp) {
        coord.i += 1;
    }

    if (!checkMoveLegalness(temp)) { return false; }
    for (coords &coord: blockCoordsList) {
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) {
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp);
    draw();
    return true;
}

void Figure::moveLeft() {
    std::vector<coords> temp(blockCoordsList);

    for (coords &coord: temp) {
        coord.j -= 1;
    }

    if (!checkMoveLegalness(temp)) { return; }

    for (coords &coord: blockCoordsList) {
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) {
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp);
    draw();
    return;
}

void Figure::moveRight() {
    std::vector<coords> temp(blockCoordsList);

    for (coords &coord: temp) {
        coord.j += 1;
    }

    if (!checkMoveLegalness(temp)) { return; }

    for (coords &coord: blockCoordsList) {
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) {
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp);
    draw();
    return;
}

bool Figure::checkMoveLegalness(std::vector<coords> newCoords) {
    for (coords &coord: newCoords) {
        if (coord.i > 21 || coord.j > 9) { return false; }
        if (coord.i < 0 || coord.j < 0) { return false; }
        if (field[coord.i][coord.j] == Black) {
            continue;
        }
        bool flag = true;
        for (coords &oldCoord: blockCoordsList) {
            if (oldCoord.i == coord.i && oldCoord.j == coord.j) {
                flag = false;
                break;
            }
        }
        if (flag) { return false; }
    }
    return true;
}

void Figure::draw() {
    for (coords &coord: blockCoordsList) {
        if (coord.i <= 1) { continue; }
        tetrisRenderer.drawTetrisWindowBlock(coord.i - 2, coord.j, field[(coord.i)][coord.j]);
        //tetrisRenderer.drawTetrisWindowBlock(coord.i - 2, coord.j,color);
    }
}