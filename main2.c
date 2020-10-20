#include "device_config.h"
#include "practice6.h"
#include <math.h>

enum port_dir{ output, input };
enum port_DCAC{ digital, analog };
enum led_state{ led_OFF, led_ON };
enum button_state{ pushed, no_pushed };
enum exponent { bbase=2, limit=8};

//Altas prioridades
__interrupt( high_priority ) void high_isr ( void ){
    Nop( ); // Funcion que consume cada ciclo de instruccion
}
//Definicion de prioridades bajas
__interrupt( low_priority ) void low_isr ( void ){
    Nop( );
}
void portsInit(void);
void Knight_Rider(void);
//Activacion del tiempo del LED
void Knight_Rider(void){
      int i=0;
      while (i<7){
          LATA = pow(2,i);
          __delay_ms (DELAY_SWEEP);
          i++;
      }
      i=7;
      while (i>=0){
          LATA = pow(2,i);
          __delay_ms(DELAY_SWEEP);
          i--;
      }
      return;
}

void main( void ) {
    int random;
    int led;
    portsInit( );
    LATA = 0 ;
    char inverse;
    //Ciclo infinito de la activacion del LED
    while(1){
       random = rand()%8;
       led = pow(2,random);
       LATA = led;
       //Prende un LED al azar
       __delay_ms(DELAY_500);
       inverse = LATA^0xFF;
       
       if (inverse == PORTB){
           Knight_Rider();
    }
       else{
           
           if (inverse == PORTB){
               //Activa el display Larson
               __delay_ms(DELAY_250);
               Knight_Rider();
           }
       }              
       }
}
//Inicializacion de A y B
void portsInit( void ){
    ANSELB = digital;
    TRISB = 0b11111111;
    ANSELA = digital;
    TRISA = 0b00000000;
}