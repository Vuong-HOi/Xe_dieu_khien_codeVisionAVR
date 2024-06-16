#ifndef GPIO_H
#define GPIO_H
#include <mega328p.h>


#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1


void pinMode(int pin, int mode){
    if (mode){
        if (pin<0){}
        else if (pin < 8) {
            DDRD |= 1 << pin; 
        } else if (pin < 14) {
            pin -= 8;
            DDRB |= 1 << pin; 
        }
        
    } else {
        if (pin<0){}
        else if (pin < 8) {
            DDRD &= ~(1 << pin); 
            PORTD |= 1 << pin; 
        } else if (pin < 14) {
            pin -= 8;
            DDRB &= ~(1 << pin); 
            PORTB |= 1 << pin; 
        }
    }
}

int digitalRead(int pin) {
    if (pin<0){
        return -1;
        }
    else if (pin < 8) {
        switch (pin){
            case 0: return PIND.0;
            case 1: return PIND.1;
            case 2: return PIND.2;
            case 3: return PIND.3;
            case 4: return PIND.4;
            case 5: return PIND.5;
            case 6: return PIND.6;
            case 7: return PIND.7;
        } 
    } else if (pin < 14) {
        pin -= 8;
        switch (pin){
            case 0: return PINB.0;
            case 1: return PINB.1;
            case 2: return PINB.2;
            case 3: return PINB.3;
            case 4: return PINB.4;
            case 5: return PINB.5;
            case 6: return PINB.6;
            case 7: return PINB.7;
        }
    }
    else{
        return -1;
    }
}

void digitalWrite(int pin, int value) {
    if (value){
        if (pin<0){}
        else if (pin < 8) {
            PORTD |= 1 << pin; 
        } else if (pin < 14) {
            pin -= 8;
            PORTB |= 1 << pin; 
        }
        
    } else {
        if (pin<0){}
        else if (pin < 8) {
            PORTD &= ~(1 << pin); 
        } else if (pin < 14) {
            pin -= 8;
            PORTB &= ~(1 << pin); 
        }
    }
}

#endif 
