#include "wifiOTA.h"


#include <WiFi.h>
#include <ArduinoOTA.h>

#include "../../include/credentials.h"

static bool connectedToWifi = false;
static unsigned long lastAttempt = 0;

#define RETRY_WIFI_TIME_MINS ((10 * 60) * 60)

void wifiOTAInit(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(HOSTNAME);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
        ArduinoOTA.setHostname(HOSTNAME);
        ArduinoOTA.begin();
    }
}


void wifiOTACheck(void)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        ArduinoOTA.handle();
    }
    else
    {
        unsigned long currentMillis = millis();
        if (currentMillis - lastAttempt >= RETRY_WIFI_TIME_MINS)
        {
            WiFi.begin(WIFI_SSID, WIFI_PASS);
            if (WiFi.waitForConnectResult() == WL_CONNECTED)
            {
                ArduinoOTA.setHostname(HOSTNAME);
                ArduinoOTA.begin();
                lastAttempt = currentMillis;
                connectedToWifi = true;
            }
        }
    }
}