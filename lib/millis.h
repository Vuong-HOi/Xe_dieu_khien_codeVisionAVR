#ifndef _MILLIS_H_
#define _MILLIS_H_

unsigned long millis_value = 0;

interrupt [TIM1_COMPA] void timer1_comp_isr(void)
{
    millis_value++;  
}
void init_millis(unsigned long f_cpu){
    unsigned long ctc_match_overflow;
    ctc_match_overflow = ((f_cpu / 1000) / 8);
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    OCR1AH = (ctc_match_overflow >> 8);
    OCR1AL = ctc_match_overflow;
    TIMSK1 |= (1 << OCIE1A);
    #asm("sei")
}

unsigned long millis (void){
    unsigned long millis_return;
    #asm("cli")
    millis_return = millis_value;
    #asm("sei")
    return millis_return;         
}

#endif

