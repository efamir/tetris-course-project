#ifndef COURSEWORK_COLOR_H
#define COURSEWORK_COLOR_H

#include <map>
#include <string>

enum Color {
    Black, BBlack, Red, BRed, Green, BGreen, Yellow, BYellow,
    Blue, BBlue, Magenta, BMagenta, Cyan, BCyan, White, BWhite
};

extern const std::map<Color, std::wstring> ColorANSI;

#endif //COURSEWORK_COLOR_H
