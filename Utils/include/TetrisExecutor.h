#ifndef COURSEWORK_TETRISEXECUTOR_H
#define COURSEWORK_TETRISEXECUTOR_H

#include "../../TetrisRenderer/include/TetrisRenderer.h"
#include "../include/InputReader.h"
#include "../include/ConfigReader.h"
#include "../../TetrisLogic/include/TetrisGame.h"

class TetrisExecutor {
    TetrisRenderer _tetrisRenderer;
    InputReader _inputReader;
public:
    TetrisExecutor();
    ~TetrisExecutor();
    void initEverything();
    void runTetrisLoop();
};


#endif //COURSEWORK_TETRISEXECUTOR_H
