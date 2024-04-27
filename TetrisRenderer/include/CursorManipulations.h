#ifndef COURSEWORK_CONSOLECURSORMANIPULATIONS_H
#define COURSEWORK_CONSOLECURSORMANIPULATIONS_H

#include <iostream>
#include <string>

void ANSICursorUp(std::ostream & stream, int n = 1, bool moveStartLine = false);
void ANSICursorDown(std::ostream & stream, int n = 1, bool moveStartLine = false);

void ANSICursorLeft(std::ostream & stream, int n = 1);
void ANSICursorRight(std::ostream & stream, int n = 1);

#endif //COURSEWORK_CONSOLECURSORMANIPULATIONS_H
