#ifndef CONFIG_H
#define CONFIG_H

/* -----------------------------------------------------
   Custom configurates
*/
/** ============================================== */
/**  Управление сенсорами  ( 1-включен/0-выключен )*/
#define USING_ODOMETER        0
#define USING_SPEEDOMETER     0

/** ============================================== */
/**  Управление моторами  ( 1-включен/0-выключен ) */
#define USING_MOTORS          1
#define USE_SERVO_1           1
#define USE_SERVO_2           1
#define USE_SERVO_3           0
#define USE_SERVO_4           0
/** ============================================== */
/// Диаметр колес в мм
#define WHILL_DIAMETER_MM     ( 70.0f )

/// Количество вырезов на энкодере колеса
#define WHILL_ENCODER_GAPS    5
/// Режим работы: 0 - без определения направления (1 сенсор на колесо)
///               1 - с определением  направления (2 сенсора на колесо)
#define WHILL_ENCODER_QUADR   0
#define PIN_WHILL_LEFT        100     
#define PIN_WHILL_RIGHT       102
#if WHILL_ENCODER_QUADR == 1
#define PIN_WHILL_LEFT_Q      101     
#define PIN_WHILL_RIGHT_Q     103
#endif
/// Постоянная времени измерений параметров колес
#define MEASURE_TIMECONST     20

/* -----------------------------------------------------
    Defaul WiFi settings
*/
/// Использовать в режиме клиента точки доступа (устройство подключается к AP)
#define USING_AP_CLIENT     1
/// Время ожидания соединения с AP в секундах 
#define AP_CLIENT_TO_S      20

/// TODO: Впишите название своей точки и пароль к ней
#define AP_NAME             "login"           
#define AP_PASSWORD         "password"

/// Использование встройнной AP
#define USING_SOFTAP        1
/// Имя и пароль для доступа к встроенной AP
#define SOFTAP_NAME         "ONBOARDAPNAME"
#define SOFTAP_PASSWORD     "ONBOARDAPPWD"

/// Использовать mDNS сервер
#define USING_MDNS_SERVER   1
/// Имя mDNS сервера
#define MDNS_SERVER_NAME    "esp-car"

/// ===============================================================================
///   Не меняйте следующие параметры
/// ===============================================================================

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
