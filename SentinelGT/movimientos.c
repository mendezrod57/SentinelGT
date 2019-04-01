//Librerias
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
//Definiciones
#include "variables.h"
#include "instrucciones.h"



volatile uint32_t tempBrazo1 = 0, tempBrazo2 = 0;
volatile uint32_t tempCamaraV = 0, tempCamaraH = 0;

void movimientos(char instruccion){
	switch(instruccion){
	case 'a':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, GARRA_DEF);
		break;
	case 'b':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, DER);
		break;
	case 'c':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, IZQ);
		break;
	case 'd':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ACELERAR);
		break;
	case 'e':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ADER);
		break;
	case 'f':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, AIZQ);
		break;
	case 'g':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RETROCEDER);
		break;
	case 'h':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RDER);
		break;
	case 'i':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RIZQ);
		break;
	case 'j':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempCamaraH++;
		if(tempCamaraH == posch){
		    tempCamaraH = 0;
		    if(camaraH < spmaxch){
		        camaraH++;
		    }else{
		        camaraH = spmaxch;
		    }
		}
		break;
	case 'k':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempCamaraH++;
		if(tempCamaraH == posch){
		    tempCamaraH = 0;
		    if(camaraH > spminch){
		        camaraH--;
		    }else{
		        camaraH = spminch;
		    }
		}
		break;
	case 'l':
	    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ACELERAR);
        tempCamaraH++;
        if(tempCamaraH == posch){
            tempCamaraH = 0;
            if(camaraH < spmaxch){
                camaraH++;
            }else{
                camaraH = spmaxch;
            }
        }
        break;
	case 'm':
	    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RETROCEDER);
        tempCamaraH++;
        if(tempCamaraH == posch){
            tempCamaraH = 0;
            if(camaraH < spmaxch){
                camaraH++;
            }else{
                camaraH = spmaxch;
            }
        }
        break;
	case 'n':
	    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ACELERAR);
        tempCamaraH++;
        if(tempCamaraH == posch){
            tempCamaraH = 0;
            if(camaraH > spminch){
                camaraH--;
            }else{
                camaraH = spminch;
            }
        }
        break;
	case 'o':
	    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RETROCEDER);
        tempCamaraH++;
        if(tempCamaraH == posch){
            tempCamaraH = 0;
            if(camaraH > spminch){
                camaraH--;
            }else{
                camaraH = spminch;
            }
        }
        break;
	case 'p':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempCamaraV++;
		if(tempCamaraV == poscv){
		    tempCamaraV = 0;
		    if(camaraV < spmaxcv){
		        camaraV++;
		    }else{
		        camaraV = spmaxcv;
		    }
		}
		break;
	case 'q':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempCamaraV++;
		if(tempCamaraV == poscv){
		    tempCamaraV = 0;
		    if(camaraV > spmincv){
		        camaraV--;
		    }else{
		        camaraV == spmincv;
		    }
		}
		break;
	case 'r':
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ACELERAR);
        tempCamaraV++;
        if(tempCamaraV == poscv){
            tempCamaraV = 0;
            if(camaraV < spmaxcv){
                camaraV++;
            }else{
                camaraV = spmaxcv;
            }
        }
        break;
	case 's':
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RETROCEDER);
        tempCamaraV++;
        if(tempCamaraV == poscv){
            tempCamaraV = 0;
            if(camaraV < spmaxcv){
                camaraV++;
            }else{
                camaraV = spmaxcv;
            }
        }
        break;
	case 't':
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, ACELERAR);
        tempCamaraV++;
        if(tempCamaraV == poscv){
            tempCamaraV = 0;
            if(camaraV > spmincv){
                camaraV--;
            }else{
                camaraV == spmincv;
            }
        }
        break;
	case 'u':
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, RETROCEDER);
        tempCamaraV++;
        if(tempCamaraV == poscv){
            tempCamaraV = 0;
            if(camaraV > spmincv){
                camaraV--;
            }else{
                camaraV == spmincv;
            }
        }
        break;
	case 'v':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempBrazo1++;
		if(tempBrazo1 == velb1){
		    tempBrazo1 = 0;
            if(brazo1 < spmaxb1){
                brazo1++;
            }else{
                brazo1 = spmaxb1;
            }
            //PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, brazo1*LoadServo/1000);
		}
		break;
	case 'w':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempBrazo1++;
		if(tempBrazo1 == velb1){
		    tempBrazo1 = 0;
            if(brazo1 > spminb1){
                brazo1--;
            }else{
                brazo1 = spminb1;
            }
            //PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, brazo1*LoadServo/1000);
		}
		break;
	case 'x':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempBrazo2++;
		if(tempBrazo2 == velb2){
		    tempBrazo2 = 0;
            if(brazo2 < spmaxb2){
                brazo2++;
            }else{
                brazo2 = spmaxb2;
            }
            //PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, brazo2*LoadServo/1000);
		}
		break;
	case 'y':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		tempBrazo2++;
		if(tempBrazo2 == velb2){
		    tempBrazo2 = 0;
            if(brazo2 > spminb2){
                brazo2--;
            }else{
                brazo2 = spminb2;
            }
            //PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, brazo2*LoadServo/1000);
		}
		break;
	case 'z':
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, ABRIR);
		break;
	case 'A':
	    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, CERRAR);
		break;
	case 'B':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		camaraV = 65;
		camaraH = 69;
		break;
	case 'C':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		lineales = 50;
		break;
	case 'D':
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		lineales = 99;
		break;
	default:
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, PARO);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_3, GARRA_DEF);
		break;
}
}
