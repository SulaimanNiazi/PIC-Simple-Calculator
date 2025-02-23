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
#include <stdio.h>
#include <stdbool.h>

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

void setDigit(double *oldValue, char *newValue, bool state){
    if(state){
        *oldValue = *oldValue * 10 + (double)(*newValue - '0');
    }
    else{
        *oldValue = *oldValue * 10 - (double)(*newValue - '0');
    }
    LCDdisplay(newValue);
    __delay_ms(300);
}
char* getInput(){
    char *output[1];
    *output = "";
    __delay_ms(300);
    while(1){
        buttonCol1 = 1;
        if(buttonRowA){
            __delay_ms(10);
            if(buttonRowA){
                *output = "7";
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                *output = "4";
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                *output = "1";
            }
        }
        else if(buttonRowD){ //  C/on Clear button
            __delay_ms(10);
            if(buttonRowD){
                *output = "C";
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
                *output = "8";
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                *output = "5";
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                *output = "2";
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                *output = "0";
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
                *output = "9";
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                *output = "6";
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                *output = "3";
            }
        }
        else if(buttonRowD){ // = equals button
            __delay_ms(10);
            if(buttonRowD){
                *output = "=";
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
                *output = "/";
            }
        }
        else if(buttonRowB){
            __delay_ms(10);
            if(buttonRowB){
                *output = "x";
            }
        }
        else if(buttonRowC){
            __delay_ms(10);
            if(buttonRowC){
                *output = "-";
            }
        }
        else if(buttonRowD){
            __delay_ms(10);
            if(buttonRowD){
                *output = "+";
            }
        }
        else{
            __delay_ms(10);
        }
        buttonCol4 = 0;
        if(strlen(*output)){
            return *output;
        }
    }
}
char* calculate(double *num1, char operator, double *num2){
    static char result[16] = {};
    switch(operator){
        case '-':
        *num1 -= *num2;
        break;

        case 'x':
        *num1 *= *num2;
        break;

        case '/':
        *num1 /= *num2;
        break;
        
        default:
        *num1 += *num2;
    }
    *num2 = 0;
    snprintf(result, 16, "%f", *num1);
    for(uint16_t x = strlen(result) - 1; x >= 0; x--){
        if(result[x] == '0'){
            result[x] = '\0';
        }
        else{
            if(result[x] == '.'){
                result[x] = '\0';
            }
            break;
        }
    }
    return result;
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
    for(uint16_t x = 0; x < 3; x++){
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
    
    char output[16], operator = '+';
    double values[2] = {0,0};
    uint16_t valuesCompleted = 0;
    bool state = true;

    while(1){
        char *newInput[1];
        *newInput = getInput();
        switch(*newInput[0]){
            case '-':
            if(state && valuesCompleted<2){
                state = false;
                if(operator != '\0'){
                    LCDdisplay(*newInput);
                    break;
                }
            }

            case '/':
            case '+':
            case 'x':
            state = true;
            operator = *newInput[0];
            switch(valuesCompleted){
                case 0:
                valuesCompleted++;
                break;

                case 1:
                strcpy(output, calculate(&values[0], operator, &values[1]));

                default:
                sendCommand(0x01);
                valuesCompleted = 1;
                LCDdisplay(output);
            }
            LCDdisplay(*newInput);
            break;

            case '=':
            strcpy(output, calculate(&values[0], operator, &values[1]));
            selectRow(2);
            LCDdisplay(output);
            selectRow(1);
            valuesCompleted = 2;
            break;

            default:
            if(*newInput[0] == 'C' || valuesCompleted == 2){
                valuesCompleted = 0;
                sendCommand(0x01);
                operator = '\0';
                values[0] = 0;
                values[1] = 0;
                state = true;
            }
            if(*newInput[0] != 'C'){
                setDigit(&values[valuesCompleted], newInput[0], state);
            }
        }
    }
}
