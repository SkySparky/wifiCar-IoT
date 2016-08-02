#include "wificar.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <Servo.h>

void MotorsDC :: tickerCB( ) {
  //Serial.println( "ticker-callback" );
}
Ticker MotorsDC :: ticker;

