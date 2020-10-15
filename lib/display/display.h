
#ifndef DISPLAY_H
#define DISPLAY_H

#include <WString.h>


void displayInit(void);
void displayPowerDown(void);
void displayTest(void);
void displayChars(const char *s, bool clear = true);
void displayString(String s, bool clear = true);
void displayPos(const char *s, uint8_t x, uint8_t y, bool clear = true);
void displayRunning(void);
void displayClear(void);


#endif