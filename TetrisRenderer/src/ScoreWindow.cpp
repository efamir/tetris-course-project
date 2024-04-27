#include "../include/ScoreWindow.h"

ScoreWindow::ScoreWindow(Cursor & cursor, uint score, uint bestScore, ScoreCoord coord)
: _cursor(cursor), _score(score), _bestScore(bestScore), _x(coord.x), _y(coord.y) {
    if (_score > _bestScore) {
        throw std::invalid_argument("Invalid argument was passed to ScoreWindow::ScoreWindow(): "
                                    "score must not be greater than bestScore."); // TODO: change exception
    }
}

void ScoreWindow::setScore(uint score) {
    if (score > _bestScore) {
        _bestScore = score;
        _bestScoreChanged = true;
    }

    _score = score;
    _totalScoreChanged = true;
}

void ScoreWindow::setBestScore(uint score) {
    if (score < _bestScore) {
        throw std::invalid_argument("Invalid argument was passed to ScoreWindow::setBestScore(): "
                                    "score must not be greater than bestScore."); // TODO: change exception
    }
    _bestScore = score;
    _bestScoreChanged = true;
}

void ScoreWindow::draw(Color scoreColor, Color bestScoreColor) { // TODO: make it beautifull maybe
    try {
        _cursor.moveTo(_x, _y);

        if (!_textIsDrawn) {
            _cursor.moveTo(_x, _y);

            for (char c: _bestScoreText) {
                _cursor.fill(c, bestScoreColor, false);
            }

            _cursor.moveTo(_x, _y + 2);
            for (char c: _totalScoreText) {
                _cursor.fill(c, scoreColor, false);
            }

            _textIsDrawn = true;
        }

        if (_bestScoreChanged) {
            _cursor.moveTo(_x, _y + 1);

            for (char c: std::to_string(_bestScore)) {
                _cursor.fill(c, bestScoreColor, false);
            }

            _bestScoreChanged = false;
        }

        if (_totalScoreChanged) {
            _cursor.moveTo(_x, _y + 3);

            for (char c: std::to_string(_score)) {
                _cursor.fill(c, scoreColor, false);
            }

            _totalScoreChanged = false;
        }
    } catch (std::out_of_range const& e) {
        throw e;
    } catch(...) {
        throw std::runtime_error("Unexpected error was caught in ScoreWindow::draw().");
    }
}
