#ifndef COURSEWORK_CONSOLECURSORMANIPULATIONS_H
#define COURSEWORK_CONSOLECURSORMANIPULATIONS_H

#include <iostream>
#include <string>

void ANSICursorUp(std::wostream & stream, int n = 1, bool moveStartLine = false);
void ANSICursorDown(std::wostream & stream, int n = 1, bool moveStartLine = false);

void ANSICursorLeft(std::wostream & stream, int n = 1);
void ANSICursorRight(std::wostream & stream, int n = 1);

void ANSIClearLine(std::wostream &stream);

#endif //COURSEWORK_CONSOLECURSORMANIPULATIONS_H
