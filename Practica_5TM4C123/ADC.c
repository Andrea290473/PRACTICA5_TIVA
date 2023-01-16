/*
 * ADC.c
 *
 *  Created on: 04/11/2019
 *      Author: ravenelco
 */
#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
       
    // 1. RCGCADC
    SYSCTL->RCGCADC |= (1<<0);
    // 2. RCGCGPIO
    SYSCTL->RCGCGPIO |= (1<<4);
    // 3. GPIOFSEL
    GPIOE->AFSEL |= 0x0e;
    // 4. GPIODEN
    GPIOE->DEN &= ~0x0e;
    // 5. GPIOAMSEL
    GPIOE->AMSEL |= 0x0e;

    /////////////// SECUENCIADOR
    // 1. ADCACTSS
    ADC0->ACTSS &= ~(0x0f);
    // 2. ADCEMUX
    ADC0->EMUX |= 0x0000;
    // 3. ADCSSMUXn
    ADC0->SSMUX0 |= 0x00000210;
    // 4. ADCSSCTLn
    ADC0->SSCTL0 |= 0x00000644;
    // 5. ADCIM
    ADC0->IM |= (0xf<<16) | (0xf<<0);
    // 6. ADCPP y ADCPC
    //ADC0_PP_R |= 0x7
    ADC0->PC |= 0x3;
    // 7. ADCACTSS
    ADC0->ACTSS |= (1<<0);
}
extern void ADC0_Leer(uint16_t data[]){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
    ADC0->PSSI |= (1<<0);
    delay_ms(1);

    while (ADC0->RIS & 0x01 == 0);
    delay_ms(1);

    while(ADC0->SSOP0 & (1<<0) == (1<<0));
    data[0] = ADC0->SSFIFO0 & 0xfff;
    delay_ms(1);
    while(ADC0->SSOP0 & (1<<4) == (1<<4));
    data[1] = ADC0->SSFIFO0 & 0xfff;
    delay_ms(1);
    while(ADC0->SSOP0 & (1<<8) == (1<<8));
    data[2] = ADC0->SSFIFO0 & 0xfff;
    delay_ms(1);

    ADC0->ISC |= (1<<0);
    delay_ms(1);
}




