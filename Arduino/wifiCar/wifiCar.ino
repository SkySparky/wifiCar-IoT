#include <Arduino.h>


// =================================================================================================================================
// TODO!!!:
// http://arduino.esp8266.com/stable/package_esp8266com_index.json         - add to board manager
// https://github.com/Links2004/arduinoWebSockets/blob/master/library.json - add to library wifisocket
// https://github.com/esp8266/arduino-esp8266fs-plugin                     - Read for upload filesystem with WEB-interface
// ==================================================================================================================================

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "wificar.h"
#include <Servo.h>
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050.h"
// ==================================================================================================================================
// TODO!!!!:
// Input name and password for you AP
const char* ssid     = "SHL";
const char* password = "SCORPION256";
// ==================================================================================================================================

//-----------------------------------------------------------
MOTORS motors;
Servo servo[ 4 ];
MPU6050 accelgyro;

ESP8266WebServer  server ( 80 );
WebSocketsServer webSocket = WebSocketsServer( 81 );
int speedX = 0, speedY = 0;
//-----------------------------------------------------------
void read_adc( )
{
  char str[ 64 ];
  yield();
  int ain =  analogRead( A0 );
  yield();
  sprintf( str , "{ \"adc\":%d }"  , ain  );
  webSocket.sendTXT( 0 ,  str , strlen( str ) );
}

bool read_accelgyro( )
{
  char str[ 64 ];
  int16_t ax, ay, az;
  int16_t gx, gy, gz;  if ( accelgyro.testConnection() )
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    sprintf( str , "{ \"accel\":[ %d,%d,%d],\"gyro\":[%d,%d,%d] }"  , ax , ay , az  , gx , gy , gz );
    yield();
    webSocket.sendTXT( 0 ,  str , strlen( str ) );
    yield();
    return true;
  }
  return false;
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght)
{
  switch (type) {
    case WStype_DISCONNECTED:
      // Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        // Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      {
        String str =  ( const char* )payload;
        int idxdd = str.indexOf(":");
        int idxdc = str.indexOf(";");
        if ( str.substring( 0 , idxdd ) == String("adc") )
        {
          read_adc( );
          //read_accelgyro( );
          break;
        }

        if ( str.substring( 0 , idxdd - 1 ) == String( "SERVO" ) )
        {
          int idx = str.charAt( idxdd - 1 ) - '0';
          if ( idx >= 1 && idx <= 4 )
          {
            int servoVal = str.substring( idxdd + 1 , idxdc ).toInt();
            servo[ idx - 1 ].write( servoVal );
          }
          break;
        }

        speedX = str.substring( idxdd + 1 , idxdc ).toInt();
        idxdd = str.lastIndexOf(":");
        idxdc = str.lastIndexOf(";");
        speedY = str.substring( idxdd + 1 , idxdc ).toInt();
        motors.setSpeed( (int)speedX , (int)speedY );
        break;
      }
    case WStype_BIN:

      break;
  }
}
// -----------------------------------------------------
String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
// -----------------------------------------------------
bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
// -----------------------------------------------------
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
}

String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

void setup()
{
  Serial.begin(115200);
  motors.begin();
  servo[ 0 ].attach( 15 );
  servo[ 1 ].attach( 16 );
  //  servo[ 2 ].attach( 1 );
  //  servo[ 3 ].attach( 2 );
  Wire.begin( );
  accelgyro.initialize(  );
  Wire.setClock( 400000 );

  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next())
    {
      String fileName = dir.fileName( );
      size_t fileSize = dir.fileSize( );
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }

  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP( ) );

  if ( MDNS.begin ( "esp-car" ) )
  {
    Serial.println( "MDNS responder started"  );
    Serial.println( "Open http://esp-car.local/" );
  }

  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");
  // Add service to MDNS-SD
  MDNS.addService( "http", "tcp", 80 );

  server.on ( "/",       [ ]( ) {
    if (!handleFileRead("/index.html")) server.send(404, "text/plain", "FileNotFound");
  });;
  server.on ( "/IMU",    [ ]( ) {
    if (!handleFileRead("/indexIMU.html")) server.send(404, "text/plain", "FileNotFound");
  });;
  server.on ( "/inline", [ ]( ) {
    server.send ( 200, "text/plain", "this works as well" );
  } );

  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop( )
{
  server.handleClient( );
  yield();
  webSocket.loop( );
  yield();
}
