
#ifndef DISPLAY_H
#define DISPLAY_H

#include <WString.h>


void displayInit(void);
void displayTest(void);
void displayChars(const char *s, bool clear = true);
void displayString(String s, bool clear = true);
void displayRunning(void);
void displayClear(void);


#endif