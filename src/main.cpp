#include <Arduino.h>

//Std Includes
#include <WiFi.h>

#include <ArduinoOTA.h>

// Local includes
#include "display.h"
#include "wifiOTA.h"
#include "gps.h"

#define LOOP_INTERVAL 1000


void setup() {
  Serial.begin(9600);
  printf("Started\n\r");
  displayInit();
  wifiOTAInit();
  gpsInit();

  printf("Setup Completed\n\r");
  displayChars("Complete.", true);
  displayString(WiFi.localIP().toString());
  

  //OTA Handlers
  ArduinoOTA.onStart([]()
  {
    displayChars("Programing...", true);
  });

}

void loop() {
  static unsigned long previousMillis = 0;
  // put your main code here, to run repeatedly:
  //Serial.print("Hello?\r\n");
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LOOP_INTERVAL) 
  {
    //displayRunning();
  	gpsTick();

    previousMillis = currentMillis;
  }


  //Must be called repeatedly
  wifiOTACheck();
  gpsFastTick();
}