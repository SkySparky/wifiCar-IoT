#ifndef WIFICARSENSORS_H
#define WIFICARSENSORS_H


  //  servo[ 2 ].attach( 1 );
  //  servo[ 3 ].attach( 2 );
//  Wire.begin( );
  //accelgyro.initialize(  );
//  Wire.setClock( 400000 );


class WifiCarSensors
{
  public:
    void read_adc( )
    {
      char str[ 64 ];
      yield();
      int ain =  analogRead( A0 );
      yield();
      sprintf( str , "{ \"adc\":%d }"  , ain  );
      //  webSocket.sendTXT( 0 ,  str , strlen( str ) );

      bool read_accelgyro( )
      {
        //  char str[ 64 ];
        //  int16_t ax, ay, az;
        //  int16_t gx, gy, gz;  if ( accelgyro.testConnection() )
        //  {
        //    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        //    sprintf( str , "{ \"accel\":[ %d,%d,%d],\"gyro\":[%d,%d,%d] }"  , ax , ay , az  , gx , gy , gz );
        //    yield();
        //    webSocket.sendTXT( 0 ,  str , strlen( str ) );
        //    yield();
        //    return true;
        //  }
        return false;
      }
    }
}

#endif
