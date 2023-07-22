/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "ConfgADC.h"
#define _XTAL_FREQ 4000000 //4MHz

void adc_init(int channel){
    
    PIR1bits.ADIF = 0;   //Inicializar bandera en 0
    PIE1bits.ADIE = 1;   //Habilitar interrupciones analogicas

    ADCON1bits.ADFM = 0; //Justificado a la izquierda
    ADCON1bits.VCFG0 = 0; //Referencia en VDD
    ADCON1bits.VCFG1 = 0; //Referencia en VSS 
    
    ADCON0bits.ADCS = 0b01; //ADCS <1:0> -> 01 Fosc/8
    
    //for (int channel = 5; channel <= 7; channel++) {
    ADCON0bits.CHS = channel; // Configura los canales a usar
    //}
    
    ADCON0bits.ADON = 1;    //Encender ADC
    __delay_us(50);
}

int adc_read(void){
    
    return ADRESH;
}

void adc_change_channel(int channel){
    
    if (channel >= 5 | channel <= 5){
        ADCON0bits.CHS = channel;
    }
    else{
    ADCON0bits.CHS = 5;
    }
    return;
}

int adc_get_channel(void){
    
    return ADCON0bits.CHS;
    
}
