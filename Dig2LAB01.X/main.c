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
 
}

//************************************************************************************
//************************************************************************************
// FUNCION PRINCIPAL
//************************************************************************************
void main(void){
    setup();
    
    if (PORTBbits.RB2 == 0) { //SUMA
            // Esperar un tiempo para filtrar los rebotes
            __delay_ms(20);
            
            // Verificar nuevamente si el botón sigue siendo presionado
            if (PORTBbits.RB2 == 0) {
                // El botón ha sido presionado correctamente
                PORTA++;
            }
    }
    
    if (PORTBbits.RB0 == 0) { //RESTA
            // Esperar un tiempo para filtrar los rebotes
            __delay_ms(20);
            
            // Verificar nuevamente si el botón sigue siendo presionado
            if (PORTBbits.RB0 == 0) {
                // El botón ha sido presionado correctamente
                PORTA--;
            }
    }
}

//************************************************************************************
//************************************************************************************
// FUNCIONES
//************************************************************************************
void setup(void){
    //configuracion de pines y puertos    
    ANSEL= 0b00000000;  //configura portA como digital
    ANSELH= 0; //configura los pines de portB como digital
    
    TRISA = 0; // Configura el portA como salida
    TRISB = 0b00000101; //Configurar los botones en portB
    
    PORTA = 0;
    PORTB = 0;
    
    //configuracion de pull-ups
    OPTION_REGbits.nRBPU = 0; //Habilitamos pull-up en B
    WPUBbits.WPUB0 = 1;       //Habilitamos pull-up en los pines deseados
    WPUBbits.WPUB2 = 1;
    
    //configuracion oscilador
    OSCCONbits.IRCF = 0b0110; //4MHz
    OSCCONbits.SCS = 1;       //Utilizar el reloj interno
    
}

//************************************************************************************
