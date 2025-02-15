/*
 * File:   main.c
 * Author: SulaimanNiazi
 *
 * Created on February 6, 2025, 6:26 PM
 */

//*******Defining ports and pins***********

#define LCDdataPort     PORTB
#define LCDdataPortDIR  TRISB
#define RSpin           PORTCbits.RC0
#define RSpinDIR        TRISCbits.TRISC0
#define RWpin           PORTCbits.RC1
#define RWpinDIR        TRISCbits.TRISC1
#define Epin            PORTCbits.RC2
#define EpinDIR         TRISCbits.TRISC2

#define buttonRowA      PORTDbits.RD0
#define buttonRowADIR   TRISDbits.TRISD0
#define buttonRowB      PORTDbits.RD1
#define buttonRowBDIR   TRISDbits.TRISD1
#define buttonRowC      PORTDbits.RD2
#define buttonRowCDIR   TRISDbits.TRISD2
#define buttonRowD      PORTDbits.RD3
#define buttonRowDDIR   TRISDbits.TRISD3
#define buttonCol1      PORTDbits.RD4
#define buttonCol1DIR   TRISDbits.TRISD4
#define buttonCol2      PORTDbits.RD5
#define buttonCol2DIR   TRISDbits.TRISD5
#define buttonCol3      PORTDbits.RD6
#define buttonCol3DIR   TRISDbits.TRISD6
#define buttonCol4      PORTDbits.RD7
#define buttonCol4DIR   TRISDbits.TRISD7

//*****************************************

#define _XTAL_FREQ 20000000
#include <xc.h>
#include <string.h>
#include <builtins.h>
#include <stdint.h>
#include <stdio.h>

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
void LCDdisplay(char sentence[]){
    RSpin = 1;
    RWpin = 0;
    uint16_t lineLength = strlen(sentence);
    for(uint16_t ind = 0; ind < lineLength; ind++){
        LCDdataPort = (uint8_t)sentence[ind];
        toggleEnable();
    }
}
void selectRow(uint16_t row){
    switch(row){
        case 1: sendCommand(0x80); break;
        case 2: sendCommand(0xc0); break;
    }
}

int main(){
//Initialization of ports and pins
    
    buttonRowADIR = 1;
    buttonRowBDIR = 1;
    buttonRowCDIR = 1;
    buttonRowDDIR = 1;
    buttonCol1DIR = 0;
    buttonCol2DIR = 0;
    buttonCol3DIR = 0;
    buttonCol4DIR = 0;
    buttonCol1 = 0;
    buttonCol2 = 0;
    buttonCol3 = 0;
    buttonCol4 = 0;

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
    selectRow(1);

//Initialization of variables
    
    uint8_t line[16],  operator = '+', numEntries = 0;
    float entry[2] = {0, 0};

    while(1){
        buttonCol1 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("7");
                entry[numEntries] = entry[numEntries] * 10 + 7;
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("4");
                entry[numEntries] = entry[numEntries] * 10 + 4;
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("1");
                entry[numEntries] = entry[numEntries] * 10 + 1;
                __delay_ms(300);
            }
        }
        else if(buttonRowD){ //  C/on Clear button
            __delay_ms(10);
            if(buttonRowD){
                sendCommand(0x01);
                memset(entry, 0, sizeof(entry));
                numEntries = 0;
                operator = '+';
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(1);
        }
        buttonCol1 = 0;
        buttonCol2 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("8");
                entry[numEntries] = entry[numEntries] * 10 + 8;
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("5");
                entry[numEntries] = entry[numEntries] * 10 + 5;
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("2");
                entry[numEntries] = entry[numEntries] * 10 + 2;
                __delay_ms(300);
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                LCDdisplay("0");
                entry[numEntries] = entry[numEntries] * 10;
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(1);
        }
        buttonCol2 = 0;
        buttonCol3 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("9");
                entry[numEntries] = entry[numEntries] * 10 + 9;
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("6");
                entry[numEntries] = entry[numEntries] * 10 + 6;
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("3");
                entry[numEntries] = entry[numEntries] * 10 + 3;
                __delay_ms(300);
            }
        }
        else if(buttonRowD){ // = equals button
            __delay_ms(10);
            if(buttonRowD){
                float ans;
                switch(operator){
                    case '+': ans = entry[0] + entry[1]; break;
                    case '-': ans = entry[0] - entry[1]; break;
                    case '*': ans = entry[0] * entry[1]; break;
                    case '/': ans = entry[0] / entry[1]; break;
                }
                char output[16];
                sprintf(output, "%f", ans);
                selectRow(2);
                LCDdisplay(output);
                selectRow(1);
                memset(entry, 0, sizeof(entry));
                numEntries = 0;
                operator = '+';
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(1);
        }
        buttonCol3 = 0;
        buttonCol4 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("/");
                operator = '/';
                numEntries++;
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("x");
                operator = '*';
                numEntries++;
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("-");
                operator = '-';
                numEntries++;
                __delay_ms(300);
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                LCDdisplay("+");
                operator = '+';
                numEntries++;
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(1);
        }
        buttonCol4 = 0;
    }
}
