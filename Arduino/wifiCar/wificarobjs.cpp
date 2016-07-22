  #include "wificar.h"
  
  void MotorsDC :: tickerCB( ){ Serial.println( "ticker-callback" );  }
  Ticker MotorsDC :: ticker;
