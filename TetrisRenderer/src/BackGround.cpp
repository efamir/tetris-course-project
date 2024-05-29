#include "../include/BackGround.h"

BackGround::BackGround(BackGroundColors const& colors) : _colors(colors) {}

void BackGround::draw(std::wostream & stream, wchar_t const& ch) const {
    drawSolidLine(stream, ch);

    drawWithTwoBg(stream, ch, _colors.scoreWindowBackgroundColor, SCORE_WINDOW_ROWS);
    drawWithTetrisBg(stream, ch);

    drawWithTwoBg(stream, ch, _colors.nextPieceBackgroundColor, NEXT_ITEM_WINDOW_ROWS);

    constexpr uint SOLID_LINE_ROWS = 2;
    constexpr uint NIW_SCORE_SEPARATOR_ROW = 1;
    drawWithTetrisBg(stream, ch,ROWS - SOLID_LINE_ROWS - SCORE_WINDOW_ROWS - NIW_SCORE_SEPARATOR_ROW - NEXT_ITEM_WINDOW_ROWS);

    drawSolidLine(stream, ch);

    constexpr uint CURSOR_X_OFFSET = 1, CURSOR_Y_OFFSET = 1;
    ANSICursorUp(stream, ROWS - CURSOR_X_OFFSET);
    ANSICursorRight(stream, CURSOR_Y_OFFSET);
}

void BackGround::drawSolidLine(std::wostream & stream, wchar_t const& ch, const uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI::get(_colors.interWindowColor);
        for (uint i = 0; i < COLS; i++) stream << ch;

        stream << "\n";
    }
}

void BackGround::drawWithTwoBg(std::wostream &stream, wchar_t const& ch, Color secondBgColor, const uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI::get(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI::get(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < TETRIS_WINDOW_WIDTH; i++) stream << ch;

        stream << ColorANSI::get(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI::get(secondBgColor);
        for (uint i = 0; i < SECOND_WINDOW_WIDTH; i++) stream << ch;

        stream << ColorANSI::get(_colors.interWindowColor);
        stream << ch;

        stream << "\n";
    }
}

void BackGround::drawWithTetrisBg(std::wostream &stream, wchar_t const& ch, const uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI::get(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI::get(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < TETRIS_WINDOW_WIDTH; i++) stream << ch;

        stream << ColorANSI::get(_colors.interWindowColor);
        stream << ch;

        for (uint i = 0; i < SECOND_WINDOW_WIDTH; i++) stream << ch;

        stream << ch;

        stream << "\n";
    }
}
