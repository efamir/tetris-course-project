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
    std::vector<coords> temp; // creating vector for temporary coords

    for (const coords &coord: blockCoordsList) { // rotating each block of the figure 90 degrees around the pivot block
        int i = coord.i - blockCoordsList[pivot].i;
        int j = coord.j - blockCoordsList[pivot].j;

        int newI = blockCoordsList[pivot].i - j;
        int newJ = blockCoordsList[pivot].j + i;

        temp.push_back({newI, newJ});
    }

    if (!checkMoveLegalness(temp)) { return; } // checking if temporary coords is good

    for (coords &coord: blockCoordsList) { // replace the old coordinates with black
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) {
        field[coord.i][coord.j] = color; // placing color on the new coords
    }
    blockCoordsList = std::move(temp); // replacing old coords with new
    draw();
    return;
}

bool Figure::moveDown() {
    std::vector<coords> temp(blockCoordsList); // creating vector for temporary coords using old coords

    for (coords &coord: temp) { // incrementing all the rows coords
        coord.i++;
    }

    if (!checkMoveLegalness(temp)) { return false; } // checking if temporary coords is good
    for (coords &coord: blockCoordsList) { // replace the old coordinates with black
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) { // placing color on the new coords
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp); // replacing old coords with new
    draw();
    return true;
}

void Figure::moveLeft() {
    std::vector<coords> temp(blockCoordsList); // creating vector for temporary coords using old coords

    for (coords &coord: temp) { // decrementing all the rows coords
        coord.j--;
    }

    if (!checkMoveLegalness(temp)) { return; } // checking if temporary coords is good

    for (coords &coord: blockCoordsList) { // replace the old coordinates with black
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) { // placing color on the new coords
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp); // replacing old coords with new
    draw();
    return;
}

void Figure::moveRight() {
    std::vector<coords> temp(blockCoordsList); // creating vector for temporary coords using old coords

    for (coords &coord: temp) { // incrementing all the cols coords
        coord.j++;
    }

    if (!checkMoveLegalness(temp)) { return; } // checking if temporary coords is good

    for (coords &coord: blockCoordsList) { // replace the old coordinates with black
        field[coord.i][coord.j] = Black;
    }
    draw();
    for (coords &coord: temp) { // placing color on the new coords
        field[coord.i][coord.j] = color;
    }
    blockCoordsList = std::move(temp); // replacing old coords with new
    draw();
    return;
}

bool Figure::checkMoveLegalness(const std::vector<coords> &newCoords) const {
    for (coords const &coord: newCoords) { // checking every coord
        if (coord.i >= FieldInfo::FIELD_ROWS || coord.j >= FieldInfo::FIELD_COLS) { return false; } // if out of bounds - return false
        if (coord.i < 0 || coord.j < 0) { return false; } // if out of bounds - return false
        if (field[coord.i][coord.j] == Black) { // if field is black (empty / no figures in) continue
            continue;
        }

        // if field[i][j] is not Black, check if this coords is coords of the same figure
        bool flag = true;
        for (coords const &oldCoord: blockCoordsList) { // check if coord is in current blocks
            if (oldCoord.i == coord.i && oldCoord.j == coord.j) {
                flag = false;
                break;
            }
        }

        if (flag) { return false; } // if not in current coords - false
    }

    return true;
}

void Figure::draw() const{
    for (coords const &coord: blockCoordsList) { // drawing every block of figure
        if (coord.i <= 1) { continue; }
        tetrisRenderer.drawTetrisWindowBlock(coord.i - FieldInfo::ROW_COORDS_OFFSET, coord.j,
                                             field[(coord.i)][coord.j]);
    }
}

void Figure::drawAsNextFigure() const{ // drawing every block of figure in the next figure window
    for (int i = 0; i < FieldInfo::NEXT_FIGURE_FIELD_COLS; i++) {
        for (int j = 0; j < FieldInfo::NEXT_FIGURE_FIELD_ROWS; j++) {
            tetrisRenderer.drawNextItemWindowBlock(j, i, Black);
        }
    }
    for (coords const &coord: blockCoordsList) {
        tetrisRenderer.drawNextItemWindowBlock(coord.i, coord.j - FieldInfo::NEXT_FIGURE_COL_COORDS_OFFSET, color);
    }
}

void Figure::dropDown() { // moving figure down until it reaches bottom or stand on other figure
    while (true) {
        if (!moveDown()) { return; }
        std::this_thread::sleep_for(std::chrono::microseconds(DropDelay::DELAY_MCRS));
    }
}

// overloaded drop down with the ability to add points
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
