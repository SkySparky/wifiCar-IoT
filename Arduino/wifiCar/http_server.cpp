#include "http_server.h"
#include "config.h"

const char* ssid     = AP_NAME;
const char* password = AP_PASSWORD;

ESP8266WebServer  server( HTTPSERVER_TCPPORT );

void begin_http_server( )
{
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  int err_count_sec = AP_CLIENT_TO_S * 10;
  while ( WiFi.status( ) != WL_CONNECTED || err_count_sec-- > 0 )
  {
    delay ( 100 );
    Serial.print ( "." );
  }
  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP( ) );

#if USING_MDNS_SERVER == 1
  if ( MDNS.begin ( MDNS_SERVER_NAME ) )
  {
    Serial.println( "MDNS responder started"  );
    Serial.printf( "Open http://%s/\n" , MDNS_SERVER_NAME );
  }

#endif

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
}
