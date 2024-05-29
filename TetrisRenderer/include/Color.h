#ifndef COURSEWORK_COLOR_H
#define COURSEWORK_COLOR_H

#include <map>
#include <string>
#include <vector>

enum Color {
    Black, BBlack, Red, BRed, Green, BGreen, Yellow, BYellow,
    Blue, BBlue, Magenta, BMagenta, BCyan, Cyan, White, BWhite,
    BgBlack, BgReset
};

class ColorANSI {
protected:
    static uint _currentColorScheme;
    static const std::vector<std::map<Color, const std::wstring>> _colorSchemes;
public:
    // get ESC Code Sequence equivalent wstring to passed color
    static std::wstring get(Color const color);

    // load color scheme
    static void loadCS();
};

#endif //COURSEWORK_COLOR_H
