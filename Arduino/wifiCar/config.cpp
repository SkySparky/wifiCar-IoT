#include "config.h"
#include <Servo.h>
Servo servo[ 4 ];


void begin_servo( )
{
#if USE_SERVO_1 == 1
  servo[ 0 ].attach( PIN_SERVO_1 );
#endif
#if USE_SERVO_2 == 1
  servo[ 1 ].attach( PIN_SERVO_2 );
#endif
#if USE_SERVO_3 == 1
  servo[ 2 ].attach( PIN_SERVO_3 );
#endif
#if USE_SERVO_4 == 1
  servo[ 3 ].attach( PIN_SERVO_4 );
#endif

}
