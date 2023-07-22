/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "InterruptOnChange.h"

//Funcion para colocar la frecencia deseada
void ioc_init(char pin){
   INTCONbits.RBIF = 0; //Inicializar bandera de portB en 0
   INTCONbits.RBIE = 1; //Habilitar interrupcion del PORTB
   IOCB = pin;

}