/**
 * @file  wificarws.cpp
 * @autor Peter Gronsky
 */
#include "config.h"
#include "wificarws.h"
#include "wificar.h"
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer( WEBSOCKET_TCPPORT );

extern MotorsDC motors;


void ws_worker( )
{
  webSocket.loop( );
  yield();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght)
{
  switch (type) {
    case WStype_DISCONNECTED:
       dbg_printf_ws("[WS  ](%u) Disconnected!\r\n", num);
      break;
    
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
         dbg_printf_ws("[WS  ](%u) Connected from %d.%d.%d.%d\r\n", num, ip[0], ip[1], ip[2], ip[3]);
        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;
    
    case WStype_TEXT:
      {
        String str =  ( const char* )payload;
        dbg_printf_ws("[WS  ](%u) text input: %s\r\n" , num , payload );
        
        if( strstr( str.c_str() , "ping" ) ) { webSocket.sendTXT( num , "pong" ); }
        
        int idxdd = str.indexOf(":");
        int idxdc = str.indexOf(";");
        /*if ( str.substring( 0 , idxdd ) == String("adc") )
        {
          //          read_adc( );
          //read_accelgyro( );
          break;
        }

        if ( str.substring( 0 , idxdd - 1 ) == String( "SERVO" ) )
        {
          int idx = str.charAt( idxdd - 1 ) - '0';
          //          if ( idx >= 1 && idx <= 4 )
          //          {
          //            int servoVal = str.substring( idxdd + 1 , idxdc ).toInt();
          //            servo[ idx - 1 ].write( servoVal );
          //          }
          break;
        }*/

        String subName , subData; 
        subName = str.substring( 0 , idxdd );
        subData = str.substring( idxdd + 1 , idxdc );
        int speedX, speedY;

        if( subName == String( "X" ) ) 
        {  
          speedX = subData.toInt( );
          str = str.substring( idxdc + 1 , str.length() );
          idxdd = str.indexOf(":"); idxdc = str.indexOf(";");
          subName = str.substring( 0 , idxdd ); subData = str.substring( idxdd + 1 , idxdc );
          if( subName == String( "Y" ) )
          {
            speedY = subData.toInt( );
            
            speedX = map( speedX, -100, 100, -1023, 1023 );
            speedY = map( speedY, -100, 100, -1023, 1023 );
            
            motors.setSpeed( ( int ) speedX , ( int ) speedY ); 
            break;
          }
        }
        break;
      }
    case WStype_BIN:

      break;
  }
}


void begin_ws( )
{
  webSocket.begin( );
  webSocket.onEvent( webSocketEvent );
}


