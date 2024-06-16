#ifndef Servo_h
#define Servo_h

#include "gpio.h"

#define pinPWM 9


int T_ = 150;
int t = 0;
int n = 0;

interrupt [TIM2_COMPA] void timer2_compa_isr(void) {
    if (t==2000){
        t = 0;
        digitalWrite(pinPWM, HIGH);
        if (n==6){
            n = 0;
            TIMSK2 = (0 << OCIE2A);
        }
        n++;
    }
    else if (t>=T_){
        digitalWrite(pinPWM, LOW);
    }
    t++;
}

void servo_write(int value){
    if (value<50){
        value = 50;
    }
    if (value>250){
        value = 250;
    }
    T_ = value;
    TIMSK2 = (1 << OCIE2A);
    #asm("sei")
}

void timer2_init() {
    TCCR2A = (1 << WGM21);
    OCR2A = 19;
    TCCR2B = (1 << CS21);
    
}

void servo_init(void){
    pinMode(pinPWM, OUTPUT);
    timer2_init();
}


#endif


