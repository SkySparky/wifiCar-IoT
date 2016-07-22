#ifndef CONFIG_H
#define CONFIG_H

/* -----------------------------------------------------
 * Custom configurates
 */
#define USING_MOTORS          1
#define USING_ODOMETER        0
#define USING_SPEEDOMETER     0

#define WHILL_DIAMETER_MM     ( 70.0f )

/// The number of slots of the wheel encoder
#define WHILL_ENCODER_GAPS    5
/// The time constant measurements (ms)
#define MEASURE_TIMECONST     20

/* -----------------------------------------------------
 *  Defaul WiFi settings
 */

#define AP_NAME             "YOUAPNAME"
#define AP_PASSWORD         "YOUAPPWD"

#define USING_SOFTAP        1
#define SOFTAP_NAME         "ONBOARDAPNAME"
#define SOFTAP_PASSWORD     "ONBOARDAPPWD"

/* -----------------------------------------------------
 *  IO Pins numbers
 */

#define PIN_MOTORA_POWER      14
#define PIN_MOTORB_POWER      12

#define PIN_MOTORA_DIRECTION  0
#define PIN_MOTORB_DIRECTION  2

/* -----------------------------------------------------
 *  Derivatives constant
 */
#ifndef M_PI
#define M_PI                  ( 3.1415f )
#endif

#if ( USING_ODOMETER == 1 || USING_SPEEDOMETER == 1 ) && defined( WHILL_DIAMETER_MM ) && defined( WHILL_ENCODER_GAPS )
 )

#define WILL_LENGTH           ( WHILL_DIAMETER_MM * 3.1415f )

#endif


#endif
