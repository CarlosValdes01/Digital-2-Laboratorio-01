/* 
 * Archivo: Dig2LAB01.c
 * Dispositivo: PIC16F887
 * Autor: Carlos Julio Valdés Oajaca
 * Compilador: XC8, MPLABX v6.05
 
 * Programa: Interrupciones y librerias
 * Hardware: botones, LEDS, potenciometro y displays

 * Creado: 17 de julio, 2023
 * Última modificación: 17 de julio, 2023
 */

//************************************************************************************
// PALABRAS DE CONFIGURACION
//************************************************************************************
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//************************************************************************************
//************************************************************************************
// LIBRERIAS
//************************************************************************************
#include <xc.h>
#include <pic16f887.h>
#include <stdint.h>

#include "InterruptOnChange.h"
#include "ConfgADC.h"
#include "ConfgTMR0.h"
#include "DisplayHex.h"

#define _XTAL_FREQ 4000000 //4MHz
//************************************************************************************
//************************************************************************************
// PROTOTIPOS DE FUNCIONES
//************************************************************************************
void setup(void);

//************************************************************************************
//************************************************************************************
// VARIABLES GLOBALES
//************************************************************************************
uint8_t channel = 0x05;

int valor_ADC;
//uint8_t decenas;
//uint8_t unidades;
//uint8_t residuo;
uint8_t flag;
uint8_t disp_val [2];

uint8_t tabla [16] = {0b00111111,  //num 0
                      0b00000110,  //num 1
                      0b01011011,  //num 2
                      0b01001111,  //num 3
                      0b01100110,  //num 4
                      0b01101101,  //num 5
                      0b01111101,  //num 6
                      0b00000111,  //num 7
                      0b01111111,  //num 8
                      0b01100111,  //num 9
                      0b01110111,  //num A (10)
                      0b01111100,  //num B (11)
                      0b00111001,  //num C (12)
                      0b01011110,  //num D (13)
                      0b01111001,  //num E (14)
                      0b01110001};  //num F (15) 
//************************************************************************************
//************************************************************************************
// DEFINIR CONSTANTES
//************************************************************************************


//************************************************************************************
//************************************************************************************
// INTERRUPCIONES
//************************************************************************************
void  __interrupt() isr(void)
{
     if (INTCONbits.T0IF) //Interrupcion del tmr0
  {
      PORTD = 0; //limpiar banderas para multiplexar
      
      if (flag == 0)
      {
         PORTC = disp_val[1]; //decenas en hex
         PORTD = 2;           //multiplexea en C6
         flag = 1;
      }
      else if (flag == 1)     //unidades en hex
      {                       //multiplexea en C5
         PORTC = disp_val[0];
         PORTD = 1;
         flag = 0; 
      }
      
      TMR0 = 131; //1ms
      INTCONbits.T0IF = 0; //reiniciar tmr0
  }
////////////////////////////////////////////////////    
    if (INTCONbits.RBIF){ //INTERRUPCION DEL PORTB
                
        if (PORTBbits.RB2 == 0){ //SUMA
            PORTA++;
        }
        if (PORTBbits.RB0 == 0) { //RESTA
            PORTA--;

        }
        INTCONbits.RBIF = 0;  //limpiar bandera
    }
////////////////////////////////////////////////////    
    if(PIR1bits.ADIF == 1) //INTERRUPCION ADC
    {
       valor_ADC = adc_read();
       PIR1bits.ADIF = 0;
    }
return;
}

//************************************************************************************
//************************************************************************************
// FUNCION PRINCIPAL
//************************************************************************************
void main(void){
    TMR0_init();
    ioc_init(0x05);
    adc_init(channel);
    setup();
    ADCON0bits.GO =1;
    
    while(1){ //Loop infinito       
    
        displayHex(valor_ADC); //convertir a HEX
    
        disp_val [0] = tabla[unidades]; //convertir numero a 7seg y guardarlo en disp_val
        disp_val [1] = tabla[decenas];
        
        if (valor_ADC == PORTA){ //Comparar valores para la alarma
            PORTBbits.RB7 = 1;
        }
        else 
            PORTBbits.RB7 = 0;
        
        
        if (ADCON0bits.GO ==0){
            
            __delay_us(1000);
            ADCON0bits.GO =1;
            
        }
    }
}

//************************************************************************************
//************************************************************************************
// FUNCIONES
//************************************************************************************
void setup(void){
    //configuracion de pines y puertos    
    ANSEL= 0b00100000;  //configurar los pines de los POT y LEDs
    ANSELH= 0; //configura los pines de portB como digital
    
    TRISA = 0; // Configura el portA como salida (LEDs))
    TRISB = 0b00000101; //Configurar los botones en portB
    TRISD = 0; //displays
    TRISC = 0; //selectores
    
    TRISEbits.TRISE0 = 1;//Configurar entradas de los POT
    
    PORTA = 0; //limpiar puertos
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    //configuracion de pull-ups
    OPTION_REGbits.nRBPU = 0; //Habilitamos pull-up en B
    WPUBbits.WPUB0 = 1;       //Habilitamos pull-up en los pines deseados
    WPUBbits.WPUB2 = 1;
    
    //configuracion oscilador
    OSCCONbits.IRCF = 0b0110; //4MHz
    OSCCONbits.SCS = 1;       //Utilizar el reloj interno
    
    INTCONbits.PEIE = 1; //Habilitar interrupciones perifericas
    INTCONbits.GIE = 1; // Habilita interrupciones generales
}

//************************************************************************************