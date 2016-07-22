#include "wificar.h"

// =================================================================================================================================
// TODO!!!:
// http://arduino.esp8266.com/stable/package_esp8266com_index.json         - add to board manager
// https://github.com/Links2004/arduinoWebSockets/blob/master/library.json - add to library wifisocket
// https://github.com/esp8266/arduino-esp8266fs-plugin                     - Read for upload filesystem with WEB-interface
// ==================================================================================================================================


MotorsDC motors;
//-----------------------------------------------------------
int speedX = 0, speedY = 0;
//-----------------------------------------------------------


void setup()
{
  Serial.begin( CONSOLE_BAUDRATE );
  motors.begin( );
  begin_servo( );
  SPIFFS.begin();
  begin_http_server( );
  begin_ws( );
}

void loop( )
{
  http_server_worker( );
  ws_worker( );
}
