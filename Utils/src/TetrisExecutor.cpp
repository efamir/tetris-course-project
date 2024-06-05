#include "../include/TetrisExecutor.h"

TetrisExecutor::TetrisExecutor() = default;

void TetrisExecutor::initEverything() {
    try {
        _tetrisRenderer.initDraw();
        _inputReader.setFlags();
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (std::runtime_error const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in TetrisExecutor::initEverything().");
    }
}

TetrisExecutor::~TetrisExecutor() {
    _inputReader.resetFlags();
}

void TetrisExecutor::runTetrisLoop() {
    GameFinishStatus gameStatus;
    char inpChar;
    try {
        TetrisGame tetrisGame(_tetrisRenderer, _inputReader);
        while ((gameStatus = tetrisGame.run()) != Exit) { // while not Exit continue
            if (gameStatus == Restart) continue;

            // if Game Over
            _tetrisRenderer.drawGameOver();
            while (true) {

                // waits for user input
                while ((inpChar = _inputReader.readNextChar()) == -1) {}

                bool breakLoop = false;
                switch (inpChar) {
                    case 'q':
                        _tetrisRenderer.drawGameOver();
                        return; // exit tetris loop
                    case 'r':
                        breakLoop = true;
                        break;
                }
                if (breakLoop) break;
            }
        }
        _tetrisRenderer.drawGameOver();
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (std::runtime_error const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in TetrisExecutor::runTetrisLoop().");
    }
}
