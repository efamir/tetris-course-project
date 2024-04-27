#include "../include/TetrisRenderer.h"


struct DefaultParams {
    static constexpr int c = 43, r = 22, score = 0, bestScore = 0; // 33

    static BackGroundColors getDefaultColors() {
        BackGroundColors defaultColors;
        defaultColors.interWindowColor = Cyan;
        defaultColors.tetrisBackgroundColor = Black;
        defaultColors.scoreWindowBackgroundColor = Black;
        defaultColors.nextPieceBackgroundColor = Black;
        return defaultColors;
    }

    static std::ostream & getStream() {
        return _stream;
    }

private:
    static std::ostream & _stream;
};

std::ostream & DefaultParams::_stream = std::cout;


TetrisRenderer::TetrisRenderer()
    : _cursor(Cursor(DefaultParams::c, DefaultParams::r, DefaultParams::getStream())),
    _bg(DefaultParams::getDefaultColors()),
    _tw(_cursor), _niw(_cursor),
    _sw(_cursor, DefaultParams::score, DefaultParams::bestScore) {
    DefaultParams::getStream() << std::unitbuf;
}

TetrisRenderer::~TetrisRenderer() {
    _cursor.moveTo();
    ANSICursorDown(std::cout, DefaultParams::r);
    DefaultParams::getStream() << "\r";
}

void TetrisRenderer::setCursorUnderTheGame() {
    try {
        _cursor.moveTo();
        ANSICursorDown(std::cout, DefaultParams::r);
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
        _bg.draw(DefaultParams::getStream());
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

void TetrisRenderer::drawTetrisWindowBlock(uint rowI, uint colI, Color color, const std::string &s) {
    try {
        _tw.draw(rowI, colI, color, s);
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

void TetrisRenderer::drawNextItemWindowBlock(uint rowI, uint colI, Color color, const std::string &s) {
    try {
        _niw.draw(rowI, colI, color, s);
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
