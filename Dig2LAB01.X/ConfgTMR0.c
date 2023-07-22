/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "ConfgTMR0.h"

//Funcion para colocar la frecencia deseada
void TMR0_init (void){
    
    OPTION_REGbits.T0CS = 0; //Tmr0 como temporizador
    OPTION_REGbits.PSA = 0;  //Asignar prescaler a tmr0
    OPTION_REGbits.PS = 0b010; //Prescaler de 1:8
    TMR0 = 131; //1ms
    
    INTCONbits.TMR0IE = 1; //habilitar interrupcion del tmr0
    INTCONbits.T0IF = 0; //inicializar bandera de tmr0 en 0

}