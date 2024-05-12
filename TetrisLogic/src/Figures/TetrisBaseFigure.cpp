#include "../../include/Figures/TetrisBaseFigure.h"


//coords::coords() {i = 0; j = 0;}
coords::coords(int i, int j) {
    this->i = i;
    this->j = j;
}

std::random_device rd;
std::mt19937 engine{rd()};
std::uniform_int_distribution<int> randColor{2, 14 - 1};

//TetrisRenderer Figure::tetrisRenderer;

Figure::Figure(Color (&field)[22][10], TetrisRenderer &tetrisRenderer, Color color) : field(field), color(color),tetrisRenderer(tetrisRenderer) {
    //currentState = 0; //не надається можливість обрати випадкову початкову форму через можливе
    // винекнення проблем(або бо так у стандартному тетрісі(поле наступної фігури всього 2 блоки у висоту))
    //blockCoordsList = blockCrdsLst;
    for (coords ij: blockCoordsList) {
        field[ij.i][ij.j] = color;
    }
}

void Figure::rotate() {
    //std::vector<coords> temp(blockCoordsList);

    //int i = 0;//todo try to remake or return back

    /*
    for (coords &coord: temp) {
        coord.i += setOfCoordsToChangeToGetState[nextState][i].i;
        coord.j += setOfCoordsToChangeToGetState[nextState][i].j;
        i++;
    }*/

    //test method
    std::vector<coords> temp;

    //coords pivot(blockCoordsList[1]); //govno? //todo винести опорний блок в конструктор
    for (const coords &coord: blockCoordsList) {
        int i = coord.i - blockCoordsList[pivot].i;
        int j = coord.j - blockCoordsList[pivot].j;

        int newI = blockCoordsList[pivot].i - j;
        int newJ = blockCoordsList[pivot].j + i;

        temp.push_back({newI, newJ});
    }

    if (!checkMoveLegalness(temp)) { return; }

    //currentState = (currentState + 1) % setOfCoordsToChangeToGetState.size();

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

void Figure::drawAsNextFigure() {
    for (coords &coord: blockCoordsList) {
        tetrisRenderer.drawNextItemWindowBlock(coord.i, coord.j-3, color);
    }
}

void Figure::dropDown() {
    while (true) {
        if (!moveDown()) { return; }
        std::this_thread::sleep_for(std::chrono::microseconds(20));
    }
}