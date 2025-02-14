/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 6, 2025, 6:26 PM
 */

//*******Defining ports and pins***********

#define LCDdataPort     PORTB
#define LCDdataPortDIR  TRISB
#define Epin            PORTCbits.RC2
#define EpinDIR         TRISCbits.TRISC2
#define RSpin           PORTCbits.RC0
#define RSpinDIR        TRISCbits.TRISC0
#define RWpin           PORTCbits.RC1
#define RWpinDIR        TRISCbits.TRISC1

//*****************************************

#define _XTAL_FREQ 20000000
#include<xc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void toggleEnable(){
    Epin = 1;
    __delay_us(10);
    Epin = 0;
    __delay_ms(10);
}
void sendCommand(uint8_t command){
    RSpin = 0;
    RWpin = 0;
    LCDdataPort = command;
    toggleEnable();
}
void LCDdisplay(uint8_t line[]){
    RSpin = 1;
    RWpin = 0;
    uint16_t lineLength = strlen((char*)line) + 1;
    for(uint16_t ind = 0; ind < lineLength; ind++){
        LCDdataPort = line[ind];
        toggleEnable();
    }
}
void selectRow(uint16_t row){
    switch(row){
        case 1: sendCommand(0x80); break;
        case 2: sendCommand(0xc0); break;
    }
}

void main(){
//LCD initialization
    
    LCDdataPortDIR = 0x00;
    EpinDIR = 0;
    RSpinDIR = 0;
    RWpinDIR = 0;
    for(int x = 0; x < 3; x++){
        __delay_ms(100);
        sendCommand(0x30);
    }
    __delay_ms(100);
    sendCommand(0x38);
    sendCommand(0x08);
    sendCommand(0x01);
    sendCommand(0x06);
    sendCommand(0x0F);
    
//Initialization of variables
    
    uint8_t line[16];
    
//Main loop

    while(1){
        
    }
}
