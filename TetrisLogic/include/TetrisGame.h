#ifndef TETRISLOGICMODULE_TETRISGAME_H
#define TETRISLOGICMODULE_TETRISGAME_H

#include "Figures/TetrisBaseFigure.h"
#include "../../Utils/include/InputReader.h"
#include <memory>

enum GameFinishStatus {
    Exit, Restart, GameOver
};

namespace TetrisInfo{
    constexpr int NUM_OF_FIGURES = 6;
    constexpr int POINTS_TO_ADD = 1000;
    constexpr int BONUS_POINTS_TO_ADD = 100;
    constexpr int NUM_OF_DIFFICULTY_LEVELS = 5;
    constexpr int ROW_TO_CHECK_ON_GAME_OVER = 2;
    constexpr int COL_TO_CHECK_FROM_ON_GAME_OVER = 3;
    constexpr int COL_TO_CHECK_TO_ON_GAME_OVER = 7;
    constexpr double defaultMaxDelay = 500;//500
    constexpr double defaultMinDelay = 100;//100
    constexpr double reduceTime = 1;//10
    constexpr int CLEAR_ROW_DELAY = 125;
    constexpr int CLEAR_ROW_DIFFICULTY_BOOST = 10;

}

class TetrisGame {
    Color field[FieldInfo::FIELD_ROWS][FieldInfo::FIELD_COLS];
    std::unique_ptr<Figure> currentFigure;
    std::unique_ptr<Figure> nextFigure;
    TetrisRenderer &tetrisRenderer;
    InputReader &inputReader;
    unsigned int score;
    unsigned int bestScore;
    int difficulty;

    std::unique_ptr<Figure> generateNewFigure();
    void putNextFigure();
    bool checkOnGameOver();
    void clearRow(std::vector<int> &rowsIndex);
    void moveBlocksDown(int i);
    void reDrawField();
    void processUserInput(char ch,double &diffCheck, int &gameFinish);
    void gamePause(int &gameFinish);
    void fallDownOverTime(double &diffCheck, int &gameFinish, bool &flag, std::chrono::time_point<std::chrono::system_clock> start);
    void checkOnFullRows();
public:
    TetrisGame(TetrisRenderer &tetrisRenderer, InputReader &inputReader);
    GameFinishStatus run();
};

#endif //TETRISLOGICMODULE_TETRISGAME_H
