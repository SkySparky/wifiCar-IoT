#ifndef WIFICAR_H
#define WIFICAR_H

#include <Arduino.h>
#include <Servo.h>
#include <Ticker.h>

#include <FS.h>
#include "Wire.h"
#include "http_server.h"
#include "wificarws.h"
#include "config.h"


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


void fs_ls()
{
  Dir dir = SPIFFS.openDir("/");
  while ( dir.next( ) )
  {
    String fileName = dir.fileName( );
    size_t fileSize = dir.fileSize( );
    Serial.printf("FS File: %s/t size: %s\n", fileName.c_str( ), formatBytes( fileSize ).c_str( ) );
  }
  Serial.printf("\n");
}

/** ------------------------------------------------------------------------------------------
    Класс управления моторами
*/
class MotorsDC
{
  public:
    /**
       Конструктор
    */
    MotorsDC ( int a = PIN_MOTORA_POWER , int b = PIN_MOTORB_POWER , int da = PIN_MOTORA_DIRECTION , int db = PIN_MOTORB_DIRECTION )
      : PWMA( a ) , PWMB( b ) , DIRA( da ) , DIRB( db ) { }
    /**
        Инициализация
    */
    void begin( )
    {
      pinMode( PWMA , OUTPUT );
      pinMode( PWMB , OUTPUT );
      pinMode( DIRA , OUTPUT );
      pinMode( DIRB , OUTPUT );
      ticker.attach( 1.0 , tickerCB );
    }
    /**
       Крайние варианты скорости
    */
    enum
    {
      STOP = 0,
      MAXSPEED = PWMRANGE
    };
    /**
       Установка скорости
    */
    void setSpeed( int A , int B )
    {
      if ( abs( A ) > PWMRANGE ) {
        A = A < 0 ? -PWMRANGE : PWMRANGE;
      }
      if ( abs( B ) > PWMRANGE ) {
        B = B < 0 ? -PWMRANGE : PWMRANGE;
      }
      analogWrite( PWMA , abs( A ) );
      analogWrite( PWMB , abs( B ) );
      digitalWrite( DIRA , A < 0 ? LOW : HIGH );
      digitalWrite( DIRB , B < 0 ? LOW : HIGH );
    }
    /**
       Остановить все
    */
    void allStop( )
    {
      analogWrite( PWMA , 0 );
      analogWrite( PWMB , 0 );
    }
  private:
    static void tickerCB( );
    static Ticker ticker;
  private:
    /// Номера выводов для управления моторами
    const int PWMA, PWMB, DIRA, DIRB;
    /// Постоянная времени
    const int timeConstMs = MEASURE_TIMECONST;
};


#endif
