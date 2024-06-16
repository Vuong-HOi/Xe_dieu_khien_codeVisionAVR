#ifndef UART_H
#define UART_H

#include <mega328p.h>



#define FOSC 16000000  // Clock Speed

volatile unsigned char rxdata;
int dem = 0;


void uart_init(unsigned int baudrate) {
    unsigned int n = FOSC / baudrate / 16 - 1;
    UBRR0H = n >> 8;
    UBRR0L = n;
    UCSR0C = 0b00000110;
    UCSR0B = 0b10011000;  
    #asm ("sei")
}

void putchar(unsigned char data) {
    while (!(UCSR0A & 0b00100000));
    UDR0 = data;
}

void putstring(char *str) {
    while (*str) {
        putchar(*str); 
        if (*str == '\n')
            putchar('\r');
        str++;
    }
}

void floatToString(float num, char* buffer, int decimalPlaces) {
    int intPart = (int)num;
    int index = 0;
    int i, j;
    char temp;
    int digit;
    float decimalPart = num - (int)num;

    do {
        buffer[index++] = intPart % 10 + '0';
        intPart /= 10;
    } while (intPart != 0);

    for (i = 0, j = index - 1; i < j; i++, j--) {
        temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    buffer[index++] = '.';

    for (i = 0; i < decimalPlaces; i++) {
        decimalPart *= 10;
        digit = (int)decimalPart;
        buffer[index++] = '0' + digit;
        decimalPart -= digit;
    }

    buffer[index] = '\n';
}

interrupt [USART_RXC] void usart_rx_isr(void) {
    rxdata = UDR0;
    dem++;
}

#endif

