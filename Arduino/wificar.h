#ifndef WIFICAR_H
#define WIFICAR_H
//+---------------+----------------+--------------------------+------------------------------+
//|    D1( 14 )   |     D2( 12 )   |         D3( 0 )          |             D4( 2 )          |
//+---------------+----------------+--------------------------+------------------------------+
//| PWMA(motor A) | PWMB (motor B) | DA (direction of motor A)|    DB (direction of motor B) |
//+---------------+----------------+--------------------------+------------------------------+

class MOTORS
{
  public:
    /**
       Конструктор
    */
    MOTORS ( int a = 14 , int b = 12 , int da = 0 , int db = 2 ) : PWMA( a ) , PWMB( b ) , DIRA( da ) , DIRB( db ) {}
    /**
        Инициализация
    */
    void begin( )
    {
      pinMode( PWMA , OUTPUT );
      pinMode( PWMB , OUTPUT );
      pinMode( DIRA , OUTPUT );
      pinMode( DIRB , OUTPUT );
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
    int PWMA, PWMB, DIRA, DIRB;
};


#endif
