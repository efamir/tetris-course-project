#ifndef TETRISLOGICMODULE_TETRISGAME_H
#define TETRISLOGICMODULE_TETRISGAME_H

#include "Figures/TetrisBaseFigure.h"
#include "../../Utils/include/InputReader.h"
#include <memory>

enum GameFinishStatus {
    Exit, Restart, GameOver
};

class TetrisGame {
    Color field[22][10];
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
    void processUserInput(char ch,double &diffCheck, int &gameFinish,double minTime,double reduceTime);
    void gamePause(int &gameFinish);
    void fallDawnOverTime(double &diffCheck, int &gameFinish,bool &flag,std::chrono::time_point<std::chrono::system_clock> start,double minTime,double reduceTime);
    void checkOnFullRows();
public:
    TetrisGame(TetrisRenderer &tetrisRenderer, InputReader &inputReader);
    GameFinishStatus run();
};

#endif //TETRISLOGICMODULE_TETRISGAME_H
