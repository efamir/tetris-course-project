#ifndef COURSEWORK_SCOREWINDOW_H
#define COURSEWORK_SCOREWINDOW_H

#include "Color.h"
#include "Cursor.h"
#include <iostream>
#include <string>

typedef unsigned int uint;

namespace ScoreWindowConsts {
    constexpr uint SCORE_WINDOW_X = 21;
    constexpr uint SCORE_WINDOW_Y = 0;
}

struct ScoreCoord {
    uint x, y;
    ScoreCoord(uint _x, uint _y) : x(_x), y(_y) {}
    ScoreCoord() : x(0), y(0) {}
};

class ScoreWindow {
    Cursor & _cursor;
    uint _score, _bestScore;
    constexpr static uint WIDTH = 9;
    const uint _x, _y; // window coordinates
    const std::string _totalScoreText = "Score";
    const std::string _bestScoreText = "Top";
    bool _textIsDrawn = false, _totalScoreChanged = true, _bestScoreChanged = true;
public:
    ScoreWindow(Cursor & cursor, uint score, uint bestScore,
                ScoreCoord coord = ScoreCoord
                        (ScoreWindowConsts::SCORE_WINDOW_X, ScoreWindowConsts::SCORE_WINDOW_Y));

    void setScore(uint score);
    void setBestScore(uint score);

    // draws the scores changes
    void draw(Color scoreColor = White, Color bestScoreColor = White);
};


#endif //COURSEWORK_SCOREWINDOW_H
