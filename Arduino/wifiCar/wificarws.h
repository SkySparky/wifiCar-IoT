/**
 * @file wificarws.h
 * @brief
 */
#ifndef WIFICARWS_H
#define WIFICARWS_H

#if DEBUG_WS == 1
#define dbg_printf_ws(...) do{ Serial.printf( __VA_ARGS__ ); Serial.println(); }while( 0 )
#else
#define dbg_printf_ws(...)
#endif
/** ----------------------------------------------
 * Start web-socket interface
 */
void begin_ws( );
/** ----------------------------------------------
 * ws-worker for loop() function
 */
void ws_worker( );


#endif
