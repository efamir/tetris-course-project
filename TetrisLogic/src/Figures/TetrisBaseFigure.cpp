#include "../../include/Figures/TetrisBaseFigure.h"

namespace {
    std::random_device rd;
}
namespace Random {
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> randColor{FieldInfo::COLOR_FROM, FieldInfo::COLOR_TO};
}

coords::coords(int i, int j) {
    this->i = i;
    this->j = j;
}

Figure::Figure(Color (&field)[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS], TetrisRenderer &tetrisRenderer,
               Color color)
        : field(field), color(color),
          tetrisRenderer(tetrisRenderer) {
}

void Figure::rotate() {
    std::vector<coords> temp;

    for (const coords &coord: blockCoordsList) {
        int i = coord.i - blockCoordsList[pivot].i;
        int j = coord.j - blockCoordsList[pivot].j;

        int newI = blockCoordsList[pivot].i - j;
        int newJ = blockCoordsList[pivot].j + i;

        temp.push_back({newI, newJ});
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

bool Figure::moveDown() {
    std::vector<coords> temp(blockCoordsList);

    for (coords &coord: temp) {
        coord.i++;
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
        coord.j--;
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
        coord.j++;
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

bool Figure::checkMoveLegalness(const std::vector<coords> &newCoords) const {
    for (coords const &coord: newCoords) {
        if (coord.i >= FieldInfo::FIELD_ROWS || coord.j >= FieldInfo::FIELD_COLS) { return false; }
        if (coord.i < 0 || coord.j < 0) { return false; }
        if (field[coord.i][coord.j] == Black) {
            continue;
        }
        bool flag = true;
        for (coords const &oldCoord: blockCoordsList) {
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
        tetrisRenderer.drawTetrisWindowBlock(coord.i - FieldInfo::ROW_COORDS_OFFSET, coord.j,
                                             field[(coord.i)][coord.j]);
    }
}

void Figure::drawAsNextFigure() {
    for (int i = 0; i < FieldInfo::NEXT_FIGURE_FIELD_COLS; i++) {
        for (int j = 0; j < FieldInfo::NEXT_FIGURE_FIELD_ROWS; j++) {
            tetrisRenderer.drawNextItemWindowBlock(j, i, Black);
        }
    }
    for (coords &coord: blockCoordsList) {
        tetrisRenderer.drawNextItemWindowBlock(coord.i, coord.j - FieldInfo::NEXT_FIGURE_COL_COORDS_OFFSET, color);
    }
}

void Figure::dropDown() {
    while (true) {
        if (!moveDown()) { return; }
        std::this_thread::sleep_for(std::chrono::microseconds(DropDelay::DELAY_MCRS));
    }
}

void Figure::dropDown(unsigned int &score, int booster) {
    while (true) {
        if (!moveDown()) { return; }
        score += (booster);
        tetrisRenderer.setScore(score);
        tetrisRenderer.drawScore();
        std::this_thread::sleep_for(std::chrono::microseconds(DropDelay::DELAY_MCRS));
    }

}
Figure::~Figure() {

}
