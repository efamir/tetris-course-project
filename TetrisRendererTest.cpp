#include "TetrisRenderer/include/TetrisRenderer.h"
#include <chrono>
#include <thread>
#include <random>

int main() {
    TetrisRenderer tr;
    tr.initDraw();

    int r = 20, c = 10;

    std::random_device rd;
    std::mt19937 engine {rd()};
    std::uniform_int_distribution<int> randRow{0, r - 1};
    std::uniform_int_distribution<int> randColumn{0, c - 1};

    std::uniform_int_distribution<int> randNIWRow{0, 1};
    std::uniform_int_distribution<int> randNIWColumn{0, 3};

    std::uniform_int_distribution<int> randColor{2, 14-1};
    std::uniform_int_distribution<int> randScore{0, 999999999};

    for (int i = 0; i < 500; i++) {
        tr.drawTetrisWindowBlock(randRow(engine), randColumn(engine), static_cast<Color>(randColor(engine)));
        tr.drawNextItemWindowBlock(randNIWRow(engine), randNIWColumn(engine), static_cast<Color>(randColor(engine)));
        tr.setScore(randScore(engine));
        tr.drawScore(static_cast<Color>(randColor(engine)), static_cast<Color>(randColor(engine)));

        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    return 0;
}
