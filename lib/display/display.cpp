#include "display.h"
#include <U8x8lib.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DISPLAY_MOSI 4
#define DISPLAY_CLOCK 15
#define DISPLAY_RESET 16

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(DISPLAY_CLOCK, DISPLAY_MOSI, DISPLAY_RESET);

void displayInit() 
{
  u8x8.begin();
  //u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setFont(u8x8_font_5x8_r);
  displayTest();
}

void displayPowerDown() 
{
  u8x8.setPowerSave(1);
  digitalWrite(DISPLAY_RESET, LOW); //reset display
}

void displayTest(void) 
{
  u8x8.drawString(0, 0, "Started");
}

void displayChars(const char *s, bool clear)
{
  if( clear == true )
  {
    u8x8.clearDisplay();
  }
  u8x8.drawString(0, 0, s);
}

void displayString(String s, bool clear)
{
  displayChars(s.c_str(), clear);
}

void displayRunning(void)
{
  static uint8_t runningIndex = 0;
  static char runningText[] = {'R', 'U', 'N', 'N', 'I', 'N', 'G', '.', '.', '.', '\0'};

  runningText[7] = runningIndex > 0 ? '.' : ' ';
  runningText[8] = runningIndex > 1 ? '.' : ' ';
  runningText[9] = runningIndex > 2 ? '.' : ' ';
  //displayChars(runningText, false);

  runningIndex > 2 ? runningIndex = 0: runningIndex++;
}


void displayClear(void)
{
  u8x8.clearDisplay();
}

void displayPos(const char *s, uint8_t x, uint8_t y, bool clear)
{
  if( clear == true )
  {
    u8x8.clearDisplay();
  }
  u8x8.drawString(x, y, s);
}