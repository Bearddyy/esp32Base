#include "wifiOTA.h"


#include <WiFi.h>
#include <ArduinoOTA.h>

#include "../../include/credentials.h"

void wifiOTAInit(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(HOSTNAME);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA.setHostname(HOSTNAME);

    ArduinoOTA.begin();
}


void wifiOTACheck(void)
{
    ArduinoOTA.handle();
}