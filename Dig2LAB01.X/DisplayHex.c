/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "DisplayHex.h"

//Funcion para colocar la frecencia deseada
void displayHex(int num){
    
    decenas = (uint8_t)(num/16);
    residuo = (num%16);
    
    unidades = (residuo);
            
    return;

}