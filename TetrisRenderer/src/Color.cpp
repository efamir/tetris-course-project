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
        { // github
            {Black,    L"\033[38;5;231m"}, // #fcfdfe
            {Red,    L"\033[38;5;124m"}, // #970b16
            {Green,    L"\033[38;5;35m"}, // #07962a
            {Yellow,    L"\033[38;5;230m"}, // #f8eec7
            {Blue,    L"\033[38;5;25m"}, // #003e8a
            {Magenta,    L"\033[38;5;205m"}, // #e94691
            {Cyan,    L"\033[38;5;153m"}, // #89d1ec
            {White,    L"\033[38;5;237m"}, // #3e3e3e
            {BBlack,    L"\033[38;5;241m"}, // #666666
            {BRed,    L"\033[38;5;160m"}, // #de0000
            {BGreen,    L"\033[38;5;151m"}, // #87d5a2
            {BYellow,    L"\033[38;5;220m"}, // #f1d007
            {BBlue,    L"\033[38;5;68m"}, // #2e6cba
            {BMagenta,    L"\033[38;5;217m"}, // #ffa29f
            {BCyan,    L"\033[38;5;87m"}, // #1cfafe
            {BWhite,    L"\033[38;5;236m"}, // #2e2e2e
            {BgBlack,    L"\033[48;5;231m"}, // #fcfdfe
        },
        { // dracula
            {Black,    L"\033[38;5;59m"}, // #282a36
            {Red,    L"\033[38;5;210m"}, // #ff5555
            {Green,    L"\033[38;5;120m"}, // #50fa7b
            {Yellow,    L"\033[38;5;222m"}, // #ffb86c
            {Blue,    L"\033[38;5;159m"}, // #8be9fd
            {Magenta,    L"\033[38;5;183m"}, // #bd93f9
            {Cyan,    L"\033[38;5;212m"}, // #ff79c6
            {White,    L"\033[38;5;188m"}, // #b4c3c5
            {BBlack,    L"\033[38;5;16m"}, // #000000
            {BRed,    L"\033[38;5;210m"}, // #ff5555
            {BGreen,    L"\033[38;5;120m"}, // #50fa7b
            {BYellow,    L"\033[38;5;222m"}, // #ffb86c
            {BBlue,    L"\033[38;5;159m"}, // #8be9fd
            {BMagenta,    L"\033[38;5;183m"}, // #bd93f9
            {BCyan,    L"\033[38;5;212m"}, // #ff79c6
            {BWhite,    L"\033[38;5;231m"}, // #ffffff
            {BgBlack,    L"\033[48;5;59m"}, // #282a36
        },
        { // rosepine
            {Black,    L"\033[38;5;59m"}, // #26233a
            {BgBlack,    L"\033[48;5;59m"}, // #26233a
            {Red,    L"\033[38;5;211m"}, // #eb6f92
            {Green,    L"\033[38;5;67m"}, // #31748f
            {Yellow,    L"\033[38;5;222m"}, // #f6c177
            {Blue,    L"\033[38;5;152m"}, // #9ccfd8
            {Magenta,    L"\033[38;5;183m"}, // #c4a7e7
            {Cyan,    L"\033[38;5;224m"}, // #ebbcba
            {White,    L"\033[38;5;189m"}, // #e0def4
            {BBlack,    L"\033[38;5;103m"}, // #6e6a86
            {BRed,    L"\033[38;5;211m"}, // #eb6f92
            {BGreen,    L"\033[38;5;67m"}, // #31748f
            {BYellow,    L"\033[38;5;222m"}, // #f6c177
            {BBlue,    L"\033[38;5;152m"}, // #9ccfd8
            {BMagenta,    L"\033[38;5;183m"}, // #c4a7e7
            {BCyan,    L"\033[38;5;224m"}, // #ebbcba
            {BWhite,    L"\033[38;5;189m"}, // #e0def4
        },
        { // rosepine_dawn
            {Black,    L"\033[38;5;230m"}, // #f2e9e1
            {BgBlack,    L"\033[48;5;230m"}, // #f2e9e1
            {Red,    L"\033[38;5;174m"}, // #b4637a
            {Green,    L"\033[38;5;67m"}, // #286983
            {Yellow,    L"\033[38;5;215m"}, // #ea9d34
            {Blue,    L"\033[38;5;109m"}, // #56949f
            {Magenta,    L"\033[38;5;139m"}, // #907aa9
            {Cyan,    L"\033[38;5;180m"}, // #d7827e
            {White,    L"\033[38;5;102m"}, // #575279
            {BBlack,    L"\033[38;5;145m"}, // #9893a5
            {BRed,    L"\033[38;5;174m"}, // #b4637a
            {BGreen,    L"\033[38;5;67m"}, // #286983
            {BYellow,    L"\033[38;5;215m"}, // #ea9d34
            {BBlue,    L"\033[38;5;109m"}, // #56949f
            {BMagenta,    L"\033[38;5;139m"}, // #907aa9
            {BCyan,    L"\033[38;5;180m"}, // #d7827e
            {BWhite,    L"\033[38;5;102m"}, // #575279
        },
        { // rosepine_moon
            {Black,    L"\033[38;5;60m"}, // #393552
            {BgBlack,    L"\033[48;5;60m"}, // #393552
            {Red,    L"\033[38;5;211m"}, // #eb6f92
            {Green,    L"\033[38;5;73m"}, // #3e8fb0
            {Yellow,    L"\033[38;5;222m"}, // #f6c177
            {Blue,    L"\033[38;5;152m"}, // #9ccfd8
            {Magenta,    L"\033[38;5;183m"}, // #c4a7e7
            {Cyan,    L"\033[38;5;217m"}, // #ea9a97
            {White,    L"\033[38;5;189m"}, // #e0def4
            {BBlack,    L"\033[38;5;103m"}, // #6e6a86
            {BRed,    L"\033[38;5;211m"}, // #eb6f92
            {BGreen,    L"\033[38;5;73m"}, // #3e8fb0
            {BYellow,    L"\033[38;5;222m"}, // #f6c177
            {BBlue,    L"\033[38;5;152m"}, // #9ccfd8
            {BMagenta,    L"\033[38;5;183m"}, // #c4a7e7
            {BCyan,    L"\033[38;5;217m"}, // #ea9a97
            {BWhite,    L"\033[38;5;189m"}, // #e0def4
        },
        { // solarized_dark
            {Black,    L"\033[38;5;23m"}, // #002b36
            {BgBlack,    L"\033[48;5;23m"}, // #002b36
            {Red,    L"\033[38;5;167m"}, // #dc322f
            {Green,    L"\033[38;5;142m"}, // #859900
            {Yellow,    L"\033[38;5;180m"}, // #cf9a6b
            {Blue,    L"\033[38;5;74m"}, // #268bd2
            {Magenta,    L"\033[38;5;169m"}, // #d33682
            {Cyan,    L"\033[38;5;73m"}, // #2aa198
            {White,    L"\033[38;5;230m"}, // #eee8d5
            {BBlack,    L"\033[38;5;103m"}, // #657b83
            {BRed,    L"\033[38;5;174m"}, // #d87979
            {BGreen,    L"\033[38;5;150m"}, // #88cf76
            {BYellow,    L"\033[38;5;103m"}, // #657b83
            {BBlue,    L"\033[38;5;75m"}, // #2699ff
            {BMagenta,    L"\033[38;5;169m"}, // #d33682
            {BCyan,    L"\033[38;5;80m"}, // #43b8c3
            {BWhite,    L"\033[38;5;230m"}, // #fdf6e3
        },
        { // nord
            {Black,    L"\033[38;5;59m"}, // #2e3440
            {BgBlack,    L"\033[48;5;59m"}, // #2e3440
            {Red,    L"\033[38;5;174m"}, // #bf616a
            {Green,    L"\033[38;5;151m"}, // #a3be8c
            {Yellow,    L"\033[38;5;223m"}, // #ebcb8b
            {Blue,    L"\033[38;5;146m"}, // #81a1c1
            {Magenta,    L"\033[38;5;181m"}, // #b48ead
            {Cyan,    L"\033[38;5;152m"}, // #88c0d0
            {White,    L"\033[38;5;189m"}, // #d8dee9
            {BBlack,    L"\033[38;5;66m"}, // #4c566a
            {BRed,    L"\033[38;5;174m"}, // #bf616a
            {BGreen,    L"\033[38;5;151m"}, // #a3be8c
            {BYellow,    L"\033[38;5;223m"}, // #ebcb8b
            {BBlue,    L"\033[38;5;146m"}, // #81a1c1
            {BMagenta,    L"\033[38;5;181m"}, // #b48ead
            {BCyan,    L"\033[38;5;152m"}, // #8fbcbb
            {BWhite,    L"\033[38;5;231m"}, // #eceff4
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
