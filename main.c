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
    
    char input[16] = "";

    while(1){
        buttonCol1 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("7");
                strcat(input, "7");
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("4");
                strcat(input, "4");
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("1");
                strcat(input, "1");
                __delay_ms(300);
            }
        }
        else if(buttonRowD){ //  C/on Clear button
            __delay_ms(10);
            if(buttonRowD){
                sendCommand(0x01);
                memset(input, 0, sizeof(input));
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(10);
        }
        buttonCol1 = 0;
        buttonCol2 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("8");
                strcat(input, "8");
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("5");
                strcat(input, "5");
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("2");
                strcat(input, "2");
                __delay_ms(300);
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                LCDdisplay("0");
                strcat(input, "0");
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(10);
        }
        buttonCol2 = 0;
        buttonCol3 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("9");
                strcat(input, "9");
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("6");
                strcat(input, "6");
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("3");
                strcat(input, "3");
                __delay_ms(300);
            }
        }
        else if(buttonRowD){ // = equals button
            __delay_ms(10);
            if(buttonRowD){
                char equation[18] = "0+", output[16];
                strcat(equation, input);
                strcpy(output, equation);
                selectRow(2);
                LCDdisplay(output);
                selectRow(1);
                memset(input, 0, sizeof(input));
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(10);
        }
        buttonCol3 = 0;
        buttonCol4 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                LCDdisplay("/");
                strcat(input, "/");
                __delay_ms(300);
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                LCDdisplay("x");
                strcat(input, "x");
                __delay_ms(300);
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                LCDdisplay("-");
                strcat(input, "-");
                __delay_ms(300);
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                LCDdisplay("+");
                strcat(input, "+");
                __delay_ms(300);
            }
        }
        else{
            __delay_ms(10);
        }
        buttonCol4 = 0;
    }
}
