#include "../include/BackGround.h"

BackGround::BackGround(BackGroundColors const& colors) : _colors(colors) {}

void BackGround::draw(std::wostream & stream, wchar_t const& ch) const {
    drawSolidLine(stream, ch);

    drawWithTwoBg(stream, ch, _colors.scoreWindowBackgroundColor, scoreWindowRows);
    drawWithTetrisBg(stream, ch);

    drawWithTwoBg(stream, ch, _colors.nextPieceBackgroundColor, nextItemWindowRows);

    drawWithTetrisBg(stream, ch, rows - 2 - scoreWindowRows - 1 - nextItemWindowRows);

    drawSolidLine(stream, ch);

    ANSICursorUp(stream, rows - 1);
    ANSICursorRight(stream, 1);
}

void BackGround::drawSolidLine(std::wostream & stream, wchar_t const& ch, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        for (uint i = 0; i < cols; i++) stream << ch;

        stream << "\n";
    }
}

void BackGround::drawWithTwoBg(std::wostream &stream, wchar_t const& ch, Color secondBgColor, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI.at(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < tetrisWindowWidth; i++) stream << ch;

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI.at(secondBgColor);
        for (uint i = 0; i < secondWindowWidth; i++) stream << ch;

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << ch;

        stream << "\n";
    }
}

void BackGround::drawWithTetrisBg(std::wostream &stream, wchar_t const& ch, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        stream << ch;

        stream << ColorANSI.at(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < tetrisWindowWidth; i++) stream << ch;

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << ch;

        for (uint i = 0; i < secondWindowWidth; i++) stream << ch;

        stream << ch;

        stream << "\n";
    }
}
