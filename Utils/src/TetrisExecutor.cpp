#include "../include/TetrisExecutor.h"

TetrisExecutor::TetrisExecutor() = default;

void TetrisExecutor::initEverything() {
    _tetrisRenderer.initDraw();
    _inputReader.setFlags();
}

TetrisExecutor::~TetrisExecutor() {
    _inputReader.resetFlags();
}

void TetrisExecutor::runTetrisLoop() {
    GameFinishStatus gameStatus;
    char inpChar;
    try {
        TetrisGame tetrisGame(_tetrisRenderer, _inputReader);
        while ((gameStatus = tetrisGame.run()) != Exit) {
            if (gameStatus == Restart) continue;
            _tetrisRenderer.drawGameOver();
            while (true) {
                while ((inpChar = _inputReader.readNextChar()) == -1) {}
                bool breakLoop = false;
                switch (inpChar) {
                    case 'q':
                        _tetrisRenderer.drawGameOver();
                        return;
                    case 'r':
                        breakLoop = true;
                        break;
                }
                if (breakLoop) break;
            }
        }
        _tetrisRenderer.drawGameOver();
    } catch (std::exception const& e) {
        std::cerr << e.what();
    }
}
