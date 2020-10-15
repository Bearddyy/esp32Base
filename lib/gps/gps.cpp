#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gps.h"
#include "display.h"
/*
   This sample code tracks satellite elevations using TinyGPSCustom objects.

   Satellite numbers and elevations are not normally tracked by TinyGPS++, but 
   by using TinyGPSCustom we get around this.

   It requires the use of SoftwareSerial and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(RX) and 3(TX).
*/
static const int RXPin = 35, TXPin = 34;
static const uint32_t GPSBaud = 9600;
static const int MAX_SATELLITES = 40;
static const int PAGE_LENGTH = 40;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

double lat = 0;
double lng = 0;
double alt = 0;


void gpsInit(void)
{
    ss.begin(GPSBaud);
    Serial.print("GPS Setup\r\n");
    
    //ss.write(cfg_msg);
}

void gpsFastTick(void)
{
    while (ss.available() > 0)
    {
            char inp = ss.read();
            gps.encode(inp);
            //Serial.print(inp);
    }
}

void gpsTick(void)
{
    if( gps.location.isUpdated() || gps.altitude.isUpdated())
    {
        lat = gps.location.lat();
        lng = gps.location.lng();
        alt = gps.altitude.meters();
        Serial.print(" LAT="); Serial.print(lat, 6);
        Serial.print(" LON="); Serial.print(lng, 6);
        Serial.print(" ALT="); Serial.println(alt, 6);
        //Serial.printf("Lat: %lf, lng: %lf, alt: %lf\r\n", lat, lng, alt);
    }

    static char line[15];
    sprintf(line, "Sats: %d",gps.satellites.value());
    displayPos(line, 0, 1, false);

    sprintf(line, "Lat: %4lf",lat);
    displayPos(line, 0, 2, false);

    sprintf(line, "Lng: %4lf",lng);
    displayPos(line, 0, 3, false);
}


