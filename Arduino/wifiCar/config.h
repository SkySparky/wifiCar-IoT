#ifndef CONFIG_H
#define CONFIG_H

/* -----------------------------------------------------
   Custom configurates
*/
#define USING_MOTORS          1
#define USING_ODOMETER        0
#define USING_SPEEDOMETER     0

#define USE_SERVO_1           1
#define USE_SERVO_2           1
#define USE_SERVO_3           0
#define USE_SERVO_4           0

#define WHILL_DIAMETER_MM     ( 70.0f )

/// The number of slots of the wheel encoder
#define WHILL_ENCODER_GAPS    5
/// The time constant measurements (ms)
#define MEASURE_TIMECONST     20

/* -----------------------------------------------------
    Defaul WiFi settings
*/
#define USING_AP_CLIENT     1
#define AP_CLIENT_TO_S      20
#define AP_NAME             "SHL"
#define AP_PASSWORD         "SCORPION256"

#define USING_SOFTAP        1
#define SOFTAP_NAME         "ONBOARDAPNAME"
#define SOFTAP_PASSWORD     "ONBOARDAPPWD"


#define WEBSOCKET_TCPPORT   8081
#define HTTPSERVER_TCPPORT  80

#define USING_MDNS_SERVER   1
#define MDNS_SERVER_NAME    "esp-car"

#define CONSOLE_BAUDRATE    115200

/* -----------------------------------------------------
    IO Pins numbers
*/

#define PIN_MOTORA_POWER      14
#define PIN_MOTORB_POWER      12

#define PIN_MOTORA_DIRECTION  0
#define PIN_MOTORB_DIRECTION  2

#define PIN_SERVO_1           15
#define PIN_SERVO_2           16
#define PIN_SERVO_3           1
#define PIN_SERVO_4           2

/// -----------------------------------------------------
#define DEBUG_WS              0
#define DEBUG_HTTP            0
#define DEBUG_TCP             0
#define DEBUG_HTTP            0

void begin_servo( );

/* -----------------------------------------------------
    Derivatives constant
*/
#ifndef M_PI
#define M_PI                  ( 3.1415f )
#endif

#if ( USING_ODOMETER == 1 || USING_SPEEDOMETER == 1 ) && defined( WHILL_DIAMETER_MM ) && defined( WHILL_ENCODER_GAPS )
)

#define WILL_LENGTH           ( WHILL_DIAMETER_MM * 3.1415f )

#endif


#endif
