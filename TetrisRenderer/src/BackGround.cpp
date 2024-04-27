#include "../include/BackGround.h"

BackGround::BackGround(BackGroundColors const& colors) : _colors(colors) {}

void BackGround::draw(std::ostream & stream) const {
    drawSolidLine(stream);

    drawWithTwoBg(stream, _colors.scoreWindowBackgroundColor, scoreWindowRows);
    drawWithTetrisBg(stream);

    drawWithTwoBg(stream, _colors.nextPieceBackgroundColor, nextItemWindowRows);

    drawWithTetrisBg(stream, rows - 2 - scoreWindowRows - 1 - nextItemWindowRows);

    drawSolidLine(stream);

    ANSICursorUp(stream, rows - 1);
    ANSICursorRight(stream, 1);
}

void BackGround::drawSolidLine(std::ostream & stream, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        for (uint i = 0; i < cols; i++) stream << "█";

        stream << "\n";
    }
}

void BackGround::drawWithTwoBg(std::ostream &stream, Color secondBgColor, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        stream << "█";

        stream << ColorANSI.at(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < tetrisWindowWidth; i++) stream << "█";

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << "█";

        stream << ColorANSI.at(secondBgColor);
        for (uint i = 0; i < secondWindowWidth; i++) stream << "█";

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << "█";

        stream << "\n";
    }
}

void BackGround::drawWithTetrisBg(std::ostream &stream, uint times) const {
    for (uint _ = 0; _ < times; _++) {
        stream << ColorANSI.at(_colors.interWindowColor);
        stream << "█";

        stream << ColorANSI.at(_colors.tetrisBackgroundColor);
        for (uint i = 0; i < tetrisWindowWidth; i++) stream << "█";

        stream << ColorANSI.at(_colors.interWindowColor);
        stream << "█";

        for (uint i = 0; i < secondWindowWidth; i++) stream << "█";

        stream << "█";

        stream << "\n";
    }
}
