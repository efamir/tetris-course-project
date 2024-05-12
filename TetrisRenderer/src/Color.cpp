#include "../include/Color.h"

const std::map<Color, std::wstring> ColorANSI {
        {Black, L"\x1b[30m"},       // Black
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
};
