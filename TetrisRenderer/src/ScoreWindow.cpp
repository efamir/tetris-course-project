#include "../include/ScoreWindow.h"

ScoreWindow::ScoreWindow(Cursor & cursor, uint score, uint bestScore, ScoreCoord coord)
: _cursor(cursor), _score(score), _bestScore(bestScore), _x(coord.x), _y(coord.y) {
    if (_score > _bestScore) {
        throw std::out_of_range("Invalid argument was passed to ScoreWindow::ScoreWindow(): "
                                "score must not be greater than bestScore: score = "
                                + std::to_string(score) + "; bestScore = "
                                + std::to_string(bestScore));
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

void ScoreWindow::setBestScore(uint bestScore) {
    if (bestScore < _bestScore) {
        throw std::invalid_argument("Invalid argument was passed to ScoreWindow::setBestScore(): "
                                    "new best score must not be lower than previous. new best score = "
                                      + std::to_string(bestScore) + "; old best score = "
                                      + std::to_string(_bestScore));
    }

    _bestScore = bestScore;
    _bestScoreChanged = true;
}

void ScoreWindow::draw(Color scoreColor, Color bestScoreColor) {
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
