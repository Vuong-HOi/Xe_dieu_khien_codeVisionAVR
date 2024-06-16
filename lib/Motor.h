#ifndef Motor_h
#define Motor_h

#include "gpio.h"
#include <delay.h>


#define TIEN 2 
#define LUI 1
#define DUNG 0  

#define pinPWM1 11
#define pinPWM2 3
#define pinPWM3 6
#define pinPWM4 5

#define SH_CP 4
#define DS 8
#define ST_CP 12
#define EN 7 


int T1 = 10;
int T2 = 10;
int T3 = 10;
int T4 = 10;

int t_1 = 0;
int t_2 = 0;
int t_3 = 0;
int t_4 = 0;



interrupt [TIM0_COMPA] void timer0_compa_isr(void) {
    if (t_1==20){
        t_1 = 0;
        digitalWrite(pinPWM1, HIGH);
    }
    if (t_2==20){
        t_2 = 0;
        digitalWrite(pinPWM2, HIGH);
    }
    if (t_3==20){
        t_3 = 0;
        digitalWrite(pinPWM3, HIGH);
    }
    if (t_4==20){
        t_4 = 0;
        digitalWrite(pinPWM4, HIGH);
    }
    if (t_1>=T1){
        digitalWrite(pinPWM1, LOW);
    }
    if (t_2>=T2){
        digitalWrite(pinPWM2, LOW);
    }
    if (t_3>=T3){
        digitalWrite(pinPWM3, LOW);
    }
    if (t_4>=T4){
        digitalWrite(pinPWM4, LOW);
    }
    t_1++;
    t_2++;
    t_3++;
    t_4++;
}

void timer0_init() {
    TCCR0A = (1 << WGM01);
    OCR0A = 199;
    TCCR0B = (1 << CS01);
    TIMSK0 = (1 << OCIE0A);
    #asm("sei")
}

void send_data(unsigned int data_out){
    int i;
    for (i=0 ; i<8 ; i++){
        if ((data_out >> i) & (0x1)){
            digitalWrite(DS,HIGH);
        }
        else{
            digitalWrite(DS,LOW);
        }
        digitalWrite(SH_CP, HIGH);
        delay_us(2);
        digitalWrite(SH_CP, LOW);
        delay_us(2);
    }
    digitalWrite(ST_CP, HIGH);
    delay_us(2);
    digitalWrite(ST_CP, LOW);
}


void motor_init(void){
    pinMode(pinPWM1, OUTPUT);
    pinMode(pinPWM2, OUTPUT);
    pinMode(pinPWM3, OUTPUT);
    pinMode(pinPWM4, OUTPUT);
    pinMode(SH_CP, OUTPUT);
    pinMode(DS, OUTPUT);
    pinMode(ST_CP, OUTPUT);
    pinMode(EN, OUTPUT);
    timer0_init();
    digitalWrite(EN,LOW);
}

void motor_setSpeed(int mt, int speed){
    switch (mt){
        case 1:
            T1 = speed;
            break;
        case 2:
            T2 = speed;
            break;
        case 3:
            T3 = speed;
            break;
        case 4:
            T4 = speed;
            break;
    }
}

void motor_run(int H1, int H2, int H3, int H4){
    int M1 = H1<<4;
    int M2 = ((H2&0b10)<<2)|((H2&0b1)<<6);
    int M3 = ((H3&0b10)<<1)|(H3&1);
    int M4 = ((H4&0b10)<<6)|((H4&0b1)<<1);
    int M = M1|M2|M3|M4;
    send_data(M);
}




#endif


