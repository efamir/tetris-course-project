#include "../include/Color.h"
#include "../../Utils/include/ConfigReader.h"

uint ColorANSI::_currentColorScheme = 0;

namespace {
    const std::wstring COLOR_RESET_COLOR_STR = L"\x1b[0m";
    const std::wstring BG_RESET_COLOR_STR = L"\x1b[49m";
    const std::wstring ERROR_COLOR_STR = L"\x1b[31m";
}

std::wstring ColorANSI::get(Color const color) {
    if (color == ColorReset) return COLOR_RESET_COLOR_STR;
    if (color == BgReset) return BG_RESET_COLOR_STR;
    if (color == Error) return ERROR_COLOR_STR;
    return ColorANSI::_colorSchemes[ColorANSI::_currentColorScheme].at(color);
}

void ColorANSI::loadCS() {
    ConfigReader * configReader = ConfigReader::getInstance();
    _currentColorScheme = configReader->getColorScheme();
}

const std::vector<std::map<Color, const std::wstring>> ColorANSI::_colorSchemes = {
        { // Default
            {Black, L"\x1b[30m"},       // Black
            {BgBlack, L"\x1b[40m"},  // Black
            {BBlack, L"\x1b[90m"},      // Bright Black
            {Red, L"\x1b[31m"},         // Red
            {BRed, L"\x1b[91m"},        // Bright Red
            {Green, L"\x1b[32m"},       // Green
            {BGreen, L"\x1b[92m"},      // Bright Green
            {Yellow, L"\x1b[33m"},      // Yellow
            {BYellow, L"\x1b[93m"},     // Bright Yellow
            {Blue, L"\x1b[34m"},        // Blue
            {BBlue, L"\x1b[94m"},       // Bright Blue
            {Magenta, L"\x1b[35m"},     // Magenta
            {BMagenta, L"\x1b[95m"},    // Bright Magenta
            {Cyan, L"\x1b[36m"},        // Cyan
            {BCyan, L"\x1b[96m"},       // Bright Cyan
            {White, L"\x1b[37m"},       // White
            {BWhite, L"\x1b[97m"}       // Bright White
        },
        { // gruvbox
            {Black,    L"\033[38;5;230m"}, // #fbf1c7
            {Red,    L"\033[38;5;167m"}, // #cc241d
            {Green,    L"\033[38;5;143m"}, // #98971a
            {Yellow,    L"\033[38;5;179m"}, // #d79921
            {Blue,    L"\033[38;5;73m"}, // #458588
            {Magenta,    L"\033[38;5;139m"}, // #b16286
            {Cyan,    L"\033[38;5;108m"}, // #689d6a
            {White,    L"\033[38;5;102m"}, // #7c6f64
            {BBlack,    L"\033[38;5;144m"}, // #928374
            {BRed,    L"\033[38;5;124m"}, // #9d0006
            {BGreen,    L"\033[38;5;100m"}, // #79740e
            {BYellow,    L"\033[38;5;172m"}, // #b57614
            {BBlue,    L"\033[38;5;30m"}, // #076678
            {BMagenta,    L"\033[38;5;132m"}, // #8f3f71
            {BCyan,    L"\033[38;5;66m"}, // #427b58
            {BWhite,    L"\033[38;5;59m"}, // #3c3836
            {BgBlack,    L"\033[48;5;230m"}, // #fbf1c7
        },
        { // gruvbox_dark
            {Black,    L"\033[38;5;235m"}, // #282828
            {Red,    L"\033[38;5;167m"}, // #cc241d
            {Green,    L"\033[38;5;143m"}, // #98971a
            {Yellow,    L"\033[38;5;179m"}, // #d79921
            {Blue,    L"\033[38;5;73m"}, // #458588
            {Magenta,    L"\033[38;5;139m"}, // #b16286
            {Cyan,    L"\033[38;5;108m"}, // #689d6a
            {White,    L"\033[38;5;145m"}, // #a89984
            {BBlack,    L"\033[38;5;144m"}, // #928374
            {BRed,    L"\033[38;5;203m"}, // #fb4934
            {BGreen,    L"\033[38;5;185m"}, // #b8bb26
            {BYellow,    L"\033[38;5;221m"}, // #fabd2f
            {BBlue,    L"\033[38;5;145m"}, // #83a598
            {BMagenta,    L"\033[38;5;181m"}, // #d3869b
            {BCyan,    L"\033[38;5;150m"}, // #8ec07c
            {BWhite,    L"\033[38;5;223m"}, // #ebdbb2
            {BgBlack,    L"\033[48;5;235m"}, // #282828
        },
        { // solarized_light
            {Black,    L"\033[38;5;230m"}, // #fdf6e3
            {Red,    L"\033[38;5;167m"}, // #dc322f
            {Green,    L"\033[38;5;142m"}, // #859900
            {Yellow,    L"\033[38;5;178m"}, // #b58900
            {Blue,    L"\033[38;5;74m"}, // #268bd2
            {Magenta,    L"\033[38;5;169m"}, // #d33682
            {Cyan,    L"\033[38;5;73m"}, // #2aa198
            {White,    L"\033[38;5;23m"}, // #073642
            {BBlack,    L"\033[38;5;23m"}, // #002b36
            {BRed,    L"\033[38;5;166m"}, // #cb4b16
            {BGreen,    L"\033[38;5;102m"}, // #586e75
            {BYellow,    L"\033[38;5;103m"}, // #657b83
            {BBlue,    L"\033[38;5;145m"}, // #839496
            {BMagenta,    L"\033[38;5;104m"}, // #6c71c4
            {BCyan,    L"\033[38;5;145m"}, // #93a1a1
            {BWhite,    L"\033[38;5;230m"}, // #fdf6e3
            {BgBlack,    L"\033[48;5;230m"}, // #282828
        },
        { // '3024night
                {Black,    L"\033[38;5;16m"}, // #090300
                {Red,    L"\033[38;5;167m"}, // #db2d20
                {Green,    L"\033[38;5;36m"}, // #01a252
                {Yellow,    L"\033[38;5;226m"}, // #fded02
                {Blue,    L"\033[38;5;38m"}, // #01a0e4
                {Magenta,    L"\033[38;5;139m"}, // #a16a94
                {Cyan,    L"\033[38;5;189m"}, // #b5e4f4
                {White,    L"\033[38;5;145m"}, // #a5a2a2
                {BBlack,    L"\033[38;5;102m"}, // #5c5855
                {BRed,    L"\033[38;5;224m"}, // #e8bbd0
                {BGreen,    L"\033[38;5;59m"}, // #3a3432
                {BYellow,    L"\033[38;5;59m"}, // #4a4543
                {BBlue,    L"\033[38;5;138m"}, // #807d7c
                {BMagenta,    L"\033[38;5;188m"}, // #d6d5d4
                {BCyan,    L"\033[38;5;180m"}, // #cdab53
                {BWhite,    L"\033[38;5;255m"}, // #f7f7f7
                {BgBlack,    L"\033[48;5;16m"}, // #282828
        },
        { // mono_amber
            {Black,    L"\033[38;5;52m"}, // #2b1900
            {Red,    L"\033[38;5;214m"}, // #ff9400
            {Green,    L"\033[38;5;214m"}, // #ff9400
            {Yellow,    L"\033[38;5;214m"}, // #ff9400
            {Blue,    L"\033[38;5;214m"}, // #ff9400
            {Magenta,    L"\033[38;5;214m"}, // #ff9400
            {Cyan,    L"\033[38;5;208m"}, // #ff8700
            {White,    L"\033[38;5;214m"}, // #ff9400
            {BBlack,    L"\033[38;5;58m"}, // #402500
            {BRed,    L"\033[38;5;214m"}, // #ff9400
            {BGreen,    L"\033[38;5;214m"}, // #ff9400
            {BYellow,    L"\033[38;5;214m"}, // #ff9400
            {BBlue,    L"\033[38;5;214m"}, // #ff9400
            {BMagenta,    L"\033[38;5;214m"}, // #ff9400
            {BCyan,    L"\033[38;5;214m"}, // #ff9400
            {BWhite,    L"\033[38;5;214m"}, // #ff9400
            {BgBlack,    L"\033[48;5;52m"}, // #282828
        },
        { // cobalt2
                {Black,    L"\033[38;5;23m"}, // #132738
                {Red,    L"\033[38;5;196m"}, // #ff0000
                {Green,    L"\033[38;5;77m"}, // #38de21
                {Yellow,    L"\033[38;5;220m"}, // #ffe50a
                {Blue,    L"\033[38;5;32m"}, // #1460d2
                {Magenta,    L"\033[38;5;198m"}, // #ff005d
                {Cyan,    L"\033[38;5;44m"}, // #00bbbb
                {White,    L"\033[38;5;251m"}, // #cccccc
                {BBlack,    L"\033[38;5;239m"}, // #555555
                {BRed,    L"\033[38;5;196m"}, // #f40e17
                {BGreen,    L"\033[38;5;77m"}, // #3bd01d
                {BYellow,    L"\033[38;5;220m"}, // #edc809
                {BBlue,    L"\033[38;5;105m"}, // #5555ff
                {BMagenta,    L"\033[38;5;213m"}, // #ff55ff
                {BCyan,    L"\033[38;5;117m"}, // #6ae3fa
                {BWhite,    L"\033[38;5;231m"}, // #ffffff
                {BgBlack,    L"\033[48;5;23m"}, // #282828
        },
        { // kokuban
                {Black,    L"\033[38;5;22m"}, // #0d4a08
                {Red,    L"\033[38;5;173m"}, // #d84e4c
                {Green,    L"\033[38;5;150m"}, // #95da5a
                {Yellow,    L"\033[38;5;186m"}, // #d6e264
                {Blue,    L"\033[38;5;74m"}, // #4b9ed7
                {Magenta,    L"\033[38;5;140m"}, // #945fc5
                {Cyan,    L"\033[38;5;179m"}, // #d89b25
                {White,    L"\033[38;5;188m"}, // #d8e2d7
                {BBlack,    L"\033[38;5;72m"}, // #34934f
                {BRed,    L"\033[38;5;210m"}, // #ff4f59
                {BGreen,    L"\033[38;5;156m"}, // #aff56a
                {BYellow,    L"\033[38;5;228m"}, // #fcff75
                {BBlue,    L"\033[38;5;111m"}, // #57aeff
                {BMagenta,    L"\033[38;5;141m"}, // #ae63e9
                {BCyan,    L"\033[38;5;215m"}, // #ffaa2b
                {BWhite,    L"\033[38;5;231m"}, // #fffefe
                {BgBlack,    L"\033[48;5;22m"}, // #282828
        },
        { // kibble
                {Black,    L"\033[38;5;16m"}, // #0e100a
                {Red,    L"\033[38;5;161m"}, // #c70031
                {Green,    L"\033[38;5;76m"}, // #29cf13
                {Yellow,    L"\033[38;5;184m"}, // #d8e30e
                {Blue,    L"\033[38;5;62m"}, // #3449d1
                {Magenta,    L"\033[38;5;129m"}, // #8400ff
                {Cyan,    L"\033[38;5;37m"}, // #0798ab
                {White,    L"\033[38;5;188m"}, // #e2d1e3
                {BBlack,    L"\033[38;5;240m"}, // #5a5a5a
                {BRed,    L"\033[38;5;198m"}, // #f01578
                {BGreen,    L"\033[38;5;114m"}, // #6ce05c
                {BYellow,    L"\033[38;5;229m"}, // #f3f79e
                {BBlue,    L"\033[38;5;147m"}, // #97a4f7
                {BMagenta,    L"\033[38;5;183m"}, // #c495f0
                {BCyan,    L"\033[38;5;122m"}, // #68f2e0
                {BWhite,    L"\033[38;5;231m"}, // #ffffff
                {BgBlack,    L"\033[48;5;16m"}, // #282828
        },
        { // japanesque
                {Black,    L"\033[38;5;234m"}, // #1e1e1e
                {BgBlack,    L"\033[48;5;234m"}, // #002b36
                {Red,    L"\033[38;5;168m"}, // #cf3f61
                {Green,    L"\033[38;5;114m"}, // #7bb75b
                {Yellow,    L"\033[38;5;221m"}, // #e9b32a
                {Blue,    L"\033[38;5;74m"}, // #4c9ad4
                {Magenta,    L"\033[38;5;140m"}, // #a57fc4
                {Cyan,    L"\033[38;5;73m"}, // #389aad
                {White,    L"\033[38;5;231m"}, // #fafaf6
                {BBlack,    L"\033[38;5;102m"}, // #595b59
                {BRed,    L"\033[38;5;181m"}, // #d18fa6
                {BGreen,    L"\033[38;5;101m"}, // #767f2c
                {BYellow,    L"\033[38;5;101m"}, // #78592f
                {BBlue,    L"\033[38;5;30m"}, // #135979
                {BMagenta,    L"\033[38;5;97m"}, // #604291
                {BCyan,    L"\033[38;5;116m"}, // #76bbca
                {BWhite,    L"\033[38;5;151m"}, // #b2b5ae
        },
        { // hax0r_gr33n
            {Black,    L"\033[38;5;16m"}, // #020f01
            {BgBlack,    L"\033[48;5;16m"}, // #020f01
            {Red,    L"\033[38;5;40m"}, // #15d00d
            {Green,    L"\033[38;5;40m"}, // #15d00d
            {Yellow,    L"\033[38;5;40m"}, // #15d00d
            {Blue,    L"\033[38;5;40m"}, // #15d00d
            {Magenta,    L"\033[38;5;40m"}, // #15d00d
            {Cyan,    L"\033[38;5;34m"}, // #15d00d // 40
            {White,    L"\033[38;5;34m"}, // #16b10e
            {BBlack,    L"\033[38;5;16m"}, // #001510
            {BRed,    L"\033[38;5;40m"}, // #19e20e
            {BGreen,    L"\033[38;5;40m"}, // #19e20e
            {BYellow,    L"\033[38;5;40m"}, // #19e20e
            {BBlue,    L"\033[38;5;40m"}, // #19e20e
            {BMagenta,    L"\033[38;5;40m"}, // #19e20e
            {BCyan,    L"\033[38;5;40m"}, // #19e20e
            {BWhite,    L"\033[38;5;231m"}, // #fefefe
        },
};
