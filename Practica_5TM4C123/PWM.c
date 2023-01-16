  #include "lib/include.h"


  extern void  Configura_Reg_PWM1(uint16_t freq, uint16_t duty_c)

{
  ///////////////////////////////MODULO0 GENERADOR 1 Y 0//////////////////////////////////////////

      //Enable reloj de modulo **+PWM0** pag 354
       SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo **+PWM0** pag 354
       //SYSCTL_RCGCGPIO_R |= (1<<5); //Enable reloj de GPIO Puerto B pag 340 pin 5/
       SYSCTL->RCGCGPIO |= (1<<1);//Enable reloj de GPIO Puerto B pag 340 pin 5/

       SYSCTL->RCC |= (1<<20); //dIVISOR /2 Y Activamos USEPWMDIV
       SYSCTL->RCC &=0xFFF4FFFF;

      //Función alterna para B4 Pag 672/
      GPIOB->AFSEL |= (1<<4)| (1<<6); //Función alterna para B4 y B6 Pag 672/

      GPIOB->PCTL |=(0xF0F0FFFF) | 0x04040000;  //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689/

      GPIOB->DEN |= (1<<4)|(1<<6); /* para decirle si es digital o no Pag 682*/

      PWM0->_1_CTL &=~(1<<0); //1266 Deshabilitamos registro CTL_generador1
      PWM0->_0_CTL &=~(1<<0); //1266 Deshabilitamos registro CTL_generador0

      PWM0->_1_GENA=0x0000008C;
      PWM0->_0_GENA=0x0000008C;

      PWM0->_1_LOAD = 50000; // (int)(25000000/freq); /cuentas=(fclk/2)/fpwm;   para 10khz cuentas = (25,000,000/10000)/
      PWM0->_0_LOAD = 50000;

      PWM0->_1_CMPA = duty_c; //80%=499
      PWM0->_1_CMPB = 40000; //80%=499

      PWM0->_0_CMPA = duty_c; //80%=499
      PWM0->_0_CMPB = 40000; //80%=499
     
      PWM0->_1_CTL = (1<<0);// Se activa el generador 1
      PWM0->_0_CTL = (1<<0);// Se activa el generador 0

      PWM0->ENABLE |= (1<<2)|(1<<0); //habilitar el bloque pa que pase Pag 1247/   
   

//////////////////////////////MODULO 0, GENERADOR2////////////////////////////////////////


      //Enable reloj de modulo **+PWM1** pag 354
       //SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo **+PWM0** pag 354
       //SYSCTL->RCGCGPIO |= (1<<5); //Enable reloj de GPIO Puerto B pag 340 pin 5/
       SYSCTL->RCGCGPIO |= (1<<4);//Enable reloj de GPIO Puerto E pag 340 pin 5/

       //SYSCTL->RCC |= (1<<20); //dIVISOR /2 Y Activamos USEPWMDIV
       //SYSCTL->RCC &=0xFFF0FFFF;

      //Función alterna para E4 Pag 672/
      GPIOE->AFSEL |= (1<<4); //Función alterna para E4 Pag 672/

      GPIOE->PCTL |=  (0xFFF0FFFF) | 0x00040000;  //*CORREGIR MASCARA Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689/

      GPIOE->DEN |= (1<<4); /* para decirle si es digital o no Pag 682*/

      PWM0->_2_CTL &=~(1<<0); //1266 Deshabilitamos registro CTL_generador2

      PWM0->_2_GENA=0x0000008C;

      PWM0->_2_LOAD = 50000; // (int)(25000000/freq); /cuentas=(fclk/2)/fpwm;   para 10khz cuentas = (25,000,000/10000)/

      PWM0->_2_CMPA = duty_c; //80%=4000
      PWM0->_2_CMPB = 40000; //80%=4000
     
      PWM0->_2_CTL = (1<<0);// Se activa el generador 1

      PWM0->ENABLE |=  (1<<4); //habilitar el bloque pa que pase Pag 1247/


}

       




