#include "lib/include.h"
 //uint16_t Result[2];
    //uint16_t duty=1999;
    uint8_t c;
    uint8_t num;
    uint16_t duty_c;
    uint8_t duc=25;
    char datos[32]="";
    uint16_t adc_data[3]={0};
    uint16_t *ptr;
    uint8_t i=0;
    uint16_t dcycle_S1=0;
    uint16_t dcycle_S2=0;
    uint16_t dcycle_S3=0;

int main(void)
{

   
    Configurar_GPIO();
    //Configurar_PLL(_50MHZ);  //Confiuracion de velocidad de reloj EXP1
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj EXP2
    Configura_Reg_ADC0();
    Configurar_UART2();
    Configura_Reg_PWM1(50,duty_c);//Configuro a 10khz el pwm
    
    Configurar_GPIO();
    //duty_c=1000;
    while(1)

    {
        GPIOF->DATA= (1<<1);

        
       // PWM0->_2_CMPA = duty_c; //80%=4000
        //PWM0->_1_CMPB = ;
        //ADC0_InSeq2(Result,duty); //llamada a la conversion por procesador
        //PWM0->_1_CMPB = duty[0];
        //PWM0->_1_CMPA = duty[1];
                //PWM0->_0_CMPA = 15000;
        
       //////////////////////////////EXPERIMENTO2/////////////////////////////////////
       
        //Con reloj de 20MHZ       
        //con una frecuencia de 50Hz nos da un periodo 20ms
        //(20M/8)=400,000-> se divide entre ocho para que en la siguiente cuenta el valor quepa en  16bits
        //(400,000/50)=50,000 -->cabe en 16 bits:)
        //Carga = 50,000
         //Ciclo de trabajo de los servos de 1ms-2ms
         // Valores de 2500-5000
      
      delay_ms(50);
      ADC0_Leer(adc_data);
      dcycle_S1= (uint16_t) (2500+(adc_data[0]*(2500/4095.0)));//Ciclo de trabajo Servo 0
      dcycle_S2=(uint16_t)(2500+(adc_data[1]*(2500/4095.0)));// Ciclo de trabajo  Servo 1
      dcycle_S3=(uint16_t)(2500+(adc_data[2]*(2500/4095.0))); //Ciclo de trabajo  Servo 2

      //PWM0->_0_CMPA= PWM0->_1_LOAD- (PWM0->_0_LOAD*(dcycle_S1/100.0));
      //PWM0->_1_CMPA= PWM0->_1_LOAD- (PWM0->_1_LOAD*(dcycle_S2/100.0));
      //PWM0->_2_CMPA= PWM0->_1_LOAD- (PWM0->_2_LOAD*(dcycle_S3/100.0));
      PWM0->_0_CMPA= PWM0->_0_LOAD- dcycle_S1;
      PWM0->_1_CMPA= PWM0->_1_LOAD- dcycle_S2;
      PWM0->_2_CMPA= PWM0->_2_LOAD- dcycle_S3;
     
////////////////////////////////EXPERIMETO3//////////////////////////
/*
      c=readChar();
       switch (c)
       {
       
            case 'r':
            num=readChar();
            duty_c=(num*196);
            //duty_c=10000;

             PWM0->_0_CMPA =duty_c ; 
             //PWM0->_1_CMPA = duty_c; 
             //PWM0->_2_CMPA = duty_c; 
            GPIOF->DATA= (1<<1);
            break;
       
              case 'g':
            num=readChar();
            //duty_c=10000;
            duty_c=(num*196);
            PWM0->_1_CMPA = duty_c;
            //PWM0->_2_CMPA = duty_c; 
            GPIOF->DATA= (1<<3);
            break;

             case 'b':
            num=readChar();
           duty_c=(num*196);
            PWM0->_2_CMPA = duty_c; 
            GPIOF->DATA= (1<<2);
            break;

            default:
            PWM0->ENABLE |=  (0<<4)|(0<<2)|(0<<0);
       }
*/
      

    }
    

   
    }