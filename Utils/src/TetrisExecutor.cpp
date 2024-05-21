#include "../include/TetrisExecutor.h"

TetrisExecutor::TetrisExecutor() = default; // todo init TetrisLogic with TetrisRender;

void TetrisExecutor::initEverything() {
    std::setlocale(LC_ALL, "");
    _tetrisRenderer.initDraw();
    _inputReader.setFlags();
}

TetrisExecutor::~TetrisExecutor() {
    _inputReader.resetFlags();
}

void TetrisExecutor::runTetrisLoop() {
    // GameFinishStatus gameStatus;
    // char inpChar;
    // while ((gameStatus = TetrisLogic.run()) != Exit) {
    //     if (gameStatus = Restart) continue;
    //     tetrisRenderer.drawGameOver();
    //     while (true) {
    //
    //         while ((inpChar = inputReader.readNextChar()) == -1) {}
    //         swith (inpChar) {
    //             case 'q':
    //                  return;
    //             case 'r':
    //                  break;
    //         }
    //      }
    // }
}
