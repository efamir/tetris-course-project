#include "../include/Color.h"

const std::map<Color, std::string> ColorANSI {
        {Black, "\x1b[30m"},       // Black
        {BBlack, "\x1b[90m"},      // Bright Black
        {Red, "\x1b[31m"},         // Red
        {BRed, "\x1b[91m"},        // Bright Red
        {Green, "\x1b[32m"},       // Green
        {BGreen, "\x1b[92m"},      // Bright Green
        {Yellow, "\x1b[33m"},      // Yellow
        {BYellow, "\x1b[93m"},     // Bright Yellow
        {Blue, "\x1b[34m"},        // Blue
        {BBlue, "\x1b[94m"},       // Bright Blue
        {Magenta, "\x1b[35m"},     // Magenta
        {BMagenta, "\x1b[95m"},    // Bright Magenta
        {Cyan, "\x1b[36m"},        // Cyan
        {BCyan, "\x1b[96m"},       // Bright Cyan
        {White, "\x1b[37m"},       // White
        {BWhite, "\x1b[97m"}       // Bright White
};
