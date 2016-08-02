#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <Servo.h>

#include "http_server.h"
#include "config.h"

const char* ssid     = AP_NAME;
const char* password = AP_PASSWORD;

ESP8266WebServer  server( HTTPSERVER_TCPPORT );

/** ---------------------------------------------------------------
 * Get content-type by file name
 */ 
 String getContentType( String filename ) 
{
  if (server.hasArg("download"))        return "application/octet-stream";
  else if (filename.endsWith(".htm"))   return "text/html";
  else if (filename.endsWith(".html"))  return "text/html";
  else if (filename.endsWith(".css"))   return "text/css";
  else if (filename.endsWith(".js"))    return "application/javascript";
  else if (filename.endsWith(".png"))   return "image/png";
  else if (filename.endsWith(".gif"))   return "image/gif";
  else if (filename.endsWith(".jpg"))   return "image/jpeg";
  else if (filename.endsWith(".ico"))   return "image/x-icon";
  else if (filename.endsWith(".xml"))   return "text/xml";
  else if (filename.endsWith(".pdf"))   return "application/x-pdf";
  else if (filename.endsWith(".zip"))   return "application/x-zip";
  else if (filename.endsWith(".gz"))    return "application/x-gzip";
  return "text/plain";
}

/** ---------------------------------------------------------------
 * Read file from HTTP-server
 */ 
 bool handleFileRead( String path ) 
 {
  Serial.println("[HTTP] file read: " + path);
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

/** ---------------------------------------------------------------
 * Out error 404
 */ 
void handleNotFound()
{
  String message = "File Not Found\r\n";
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

/** ---------------------------------------------------------------
 * Worker for HTTP-server 
 */ 
void http_server_worker( )
{
  server.handleClient( );
  yield(); 
}

/** ---------------------------------------------------------------
 * Start HTTP-server
 */ 
void begin_http_server( )
{
  WiFi.begin ( ssid, password );
  Serial.println ( "[WiFi] Connecting to AP." );

  // Wait for connection
  int err_count_sec = AP_CLIENT_TO_S;
  while ( WiFi.status( ) != WL_CONNECTED && err_count_sec-- > 0 )
  {
    delay ( 1000 );
    Serial.print ( "." );
  }
  Serial.println( "" );
  if( err_count_sec <= 0 ) Serial.println( "[WiFi] Error connection." );
  Serial.printf( "[WiFi] Connected to %s\r\n" , ssid );
  Serial.print ( "[WiFi] IP address: " );  Serial.println ( WiFi.localIP( ) );

#if USING_MDNS_SERVER == 1
  if ( MDNS.begin ( MDNS_SERVER_NAME ) )
  {
    Serial.println( "[MDNS] responder started"  );
    Serial.printf( "[MDNS] Open http://%s.local/\r\n" , MDNS_SERVER_NAME );
  }
#endif
  // Start TCP (HTTP) server
  Serial.println("[TCP ] server started");
  // Add service to MDNS-SD
  MDNS.addService( "http", "tcp", 80 );
  // ---------------------------------------------------------------------------
  server.on( "/"                  , []() { if (!handleFileRead("/index.html")) server.send(404, "text/plain", "FileNotFound"); });;
  server.on( "/IMU"               , []() { if (!handleFileRead("/indexIMU.html")) server.send(404, "text/plain", "FileNotFound"); });;
  server.on( "/inline"            , []() { server.send ( 200, "text/plain", "this works as well" ); } );
  server.on( "/bootstrap.css"     , []() { handleFileRead( "/bootstrap.css" );} );
  server.on( "/bootstrap.js"      , []() { handleFileRead( "/bootstrap.js" );} );
  server.on( "/jquery.js"         , []() { handleFileRead( "/jquery.js"     );} );
  server.on( "/nipplejs.min.js"   , []() { handleFileRead( "/nipplejs.min.js"  );} );
  server.on( "/config.html"       , []() { handleFileRead( "/config.html"  );} );
  // ---------------------------------------------------------------------------
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "[HTTP] server started" );
}
