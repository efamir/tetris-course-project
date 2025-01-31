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
    constexpr double DEFAULT_MAX_DELAY = 500; // 500
    constexpr double DEFAULT_MIN_DELAY = 100; // 100
    constexpr double REDUCE_DELAY = 2; // 2
    constexpr int CLEAR_ROW_DELAY = 125;
    constexpr int CLEAR_ROW_DIFFICULTY_BOOST = 10;
    constexpr int NUM_OF_BLINKS = 2;
    constexpr wchar_t SHADOW_CHAR = L'░';

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
    bool checkOnGameOver() const;
    void clearRow(std::vector<int> &rowsIndex);
    void moveBlocksDown(int i);
    void reDrawField() const;
    void processUserInput(char ch,double &diffCheck, int &gameFinish);
    void gamePause(int &gameFinish);
    void fallDownOverTime(double &diffCheck, int &gameFinish, bool &flag, std::chrono::time_point<std::chrono::system_clock> start);
    void checkOnFullRows();
    void blinkingRowsAnimation(std::vector<int> rows);

public:
    TetrisGame(TetrisRenderer &tetrisRenderer, InputReader &inputReader);
    GameFinishStatus run();
};

#endif //TETRISLOGICMODULE_TETRISGAME_H
