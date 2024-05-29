#include "../include/TetrisRenderer.h"
#include "../../Utils/include/ConfigReader.h"

namespace {
    struct DefaultParams {
        static constexpr int COLS = 43, ROWS = 22, SCORE = 0, BEST_SCORE = 0;

        static BackGroundColors getDefaultColors() {
            BackGroundColors defaultColors;
            defaultColors.interWindowColor = Cyan;
            defaultColors.tetrisBackgroundColor = Black;
            defaultColors.scoreWindowBackgroundColor = Black;
            defaultColors.nextPieceBackgroundColor = Black;
            return defaultColors;
        }

        static std::wostream & getStream() {
            return _stream;
        }

    private:
        static std::wostream & _stream;
    };
}

std::wostream & DefaultParams::_stream = std::wcout;


TetrisRenderer::TetrisRenderer()
    : _cursor(Cursor(DefaultParams::COLS, DefaultParams::ROWS, DefaultParams::getStream())),
    _bg(DefaultParams::getDefaultColors()),
    _tw(_cursor), _niw(_cursor),
    _sw(_cursor, DefaultParams::SCORE, ConfigReader::getInstance()->getBestScore()),
    _gsd(_cursor) {
    DefaultParams::getStream() << std::unitbuf;
}

TetrisRenderer::~TetrisRenderer() {
    // sets the cursor under the game and resets colors
    try {
        DefaultParams::getStream() << ColorANSI::get(BgReset);
        DefaultParams::getStream() << ColorANSI::get(Black);
        setCursorUnderTheGame();
    } catch (...) {} // prevents errors in destructor
}

void TetrisRenderer::setCursorUnderTheGame() {
    try {
        _cursor.moveTo();
        ANSICursorDown(DefaultParams::getStream(), DefaultParams::ROWS);
        DefaultParams::getStream() << "\r";
    } catch (std::out_of_range const& e) {
        throw e;
    } catch (std::runtime_error const& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::setCursorUnderTheGame().");
    }
}

void TetrisRenderer::initDraw() {
    try {
        ColorANSI::loadCS();
        _bg.draw(DefaultParams::getStream());
        DefaultParams::getStream() << ColorANSI::get(BgBlack);
        _sw.draw();
        _niw.initDraw();
        _cursor.moveTo();
    } catch (std::out_of_range const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (std::runtime_error const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::initDraw().");
    }
}

void TetrisRenderer::drawTetrisWindowBlock(uint rowI, uint colI, Color color, wchar_t const& ch) {
    try {
        _tw.draw(rowI, colI, color, ch);
    } catch (std::out_of_range const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (std::runtime_error const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::drawTetrisWindowBlock().");
    }
}

void TetrisRenderer::drawNextItemWindowBlock(uint rowI, uint colI, Color color, wchar_t const& ch) {
    try {
        _niw.draw(rowI, colI, color, ch);
    } catch (std::out_of_range const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (std::runtime_error const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::drawNextItemWindowBlock().");
    }
}

void TetrisRenderer::setScore(uint score) {
    _sw.setScore(score);
}

void TetrisRenderer::drawScore(Color scoreColor, Color bestScoreColor) {
    try {
        _sw.draw(scoreColor, bestScoreColor);
    } catch (std::out_of_range const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (std::runtime_error const& e) {
        setCursorUnderTheGame();
        throw e;
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::drawScore().");
    }
}

void TetrisRenderer::drawPause() {
    try {
        _tw.clear();
        _gsd.drawPause();
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::drawPause().");
    }
}

void TetrisRenderer::drawGameOver() {
    try {
        _tw.clear();
        _gsd.drawGameOver();
    } catch (...) {
        setCursorUnderTheGame();
        throw std::runtime_error("Unexpected error was caught in TetrisRenderer::drawGameOver().");
    }
}
