#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <mega328p.h>
#include <delay.h>
#include "gpio.h"
#include "millis.h"



int pulseIn(int pin, int value, unsigned int timeout) {
    int width = 0;
    unsigned int start_time = millis();

    // Wait for the pulse to start
    while ((digitalRead(pin)) == value) {
        if ((millis() - start_time) > timeout) {
            return 0;  // Timeout
        }
    }

    // Wait for the pulse to end
    while ((digitalRead(pin)) != value) {
        if ((millis() - start_time) > timeout) {
            return 0;  // Timeout
        }
    }

    // Measure the pulse width
    start_time = millis();
    while ((digitalRead(pin)) == value) {
        if ((millis() - start_time) > timeout) {
            return 0;  // Timeout
        }
        width++;
        delay_us(1);
    }
    
    return width;
}

void init_ultrasonic(int Echo, int Trig){
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
}

float ultrasonic(int Echo, int Trig) {
    int t;
    float cm;
    digitalWrite(Trig, LOW);
    delay_us(4);
    digitalWrite(Trig, HIGH);
    delay_us(10);
    digitalWrite(Trig, LOW);
    t = pulseIn(Echo, 1, 10);
    cm = (t/2.9)/2;   // time convert distance
    return cm;
}

#endif 

