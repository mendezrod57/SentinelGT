//Librerias
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include"inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.c"
#include"driverlib/timer.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/systick.c"
#include "uartstdio.h"
#include "pinout.h"
#include "movimientos.h"
#include "variables.h"
#include "instrucciones.h"

/*-------------------------------------------------------------------------------------------------*/
/*----------------------------           DEFINICIONES             ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

//HOME DE RECOGER BRAZO2 = 66
//HOME DE RECOGER BRAZO1 = 100
/*-------------------------------------------------------------------------------------------------*/
/*----------------------------            VARIABLES               ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/
volatile uint32_t brazo1 = 45, brazo2 = 108, camaraH = 65, camaraV = 69, lineales = 50;
volatile uint32_t PWMFreq  = 50;
volatile uint32_t PWMClock = 80000000/64;
volatile uint32_t LoadServo = 24999;
volatile uint32_t tempLuz = 0, blinking = 0x04;
bool flag = false;

volatile char inst[2];
/*-------------------------------------------------------------------------------------------------*/
/*----------------------------    CONFIGURACION DE PERIFERICOS    ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------*/
/*----------------------------                PWM                 ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/
void configurePWM(void){
    //Habilitar el reloj
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
    //activar el modulo PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    //Esperar que este listo
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}

    //Configuracion para el brazo de la camara
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, LoadServo);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, camaraH*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, camaraV*LoadServo/1000);

    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT|PWM_OUT_3_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    //Configuracion para los actuadores
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, LoadServo);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, lineales*LoadServo/1000);

    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);

    //Configuracion para el brazo
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, LoadServo);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, brazo1*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, brazo2*LoadServo/1000);

    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT|PWM_OUT_5_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}

/*-------------------------------------------------------------------------------------------------*/
/*----------------------------                UART                ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

void configureUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)){}
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART0); //Habilitar interrupciones de UART
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT| UART_INT_RX);//Habilitar las interrupciones por recepcion y por timeout
}

void UART0IntHandler(void){
    uint8_t pos = 0;
    UARTIntClear(UART0_BASE, UART_INT_RX);
    while(UARTCharsAvail(UART0_BASE)){ // Inicio del ciclo siempre que exista un char recibido en el UART
        inst[pos] = UARTCharGetNonBlocking(UART0_BASE);
        //UARTCharPut(UART0_BASE,inst[pos]);
        pos++;
    }
    pos = 0;
    //UARTCharPut(UART0_BASE,'\n');
    //UARTCharPut(UART0_BASE,'\r');
}

/*-------------------------------------------------------------------------------------------------*/
/*----------------------------             FUNCIONES              ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/
void moveServo(void){
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, camaraH*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, camaraV*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, brazo1*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, brazo2*LoadServo/1000);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, lineales*LoadServo/1000);
}

void abrir(void){
    if(!flag){
    tempBrazo1++;
        if(tempBrazo1 == velb1){
            tempBrazo1 = 0;
            if(brazo1 < spmaxb1){
                brazo1++;
            }else{
                brazo1 = spmaxb1;
            }
        }
        tempBrazo2++;
        if(tempBrazo2 == velb2){
            tempBrazo2 = 0;
            if(brazo2 > spminb2){
                brazo2--;
            }else{
                brazo2 = spminb2;
            }
        }
        if((brazo1 == spmaxb1)&&(brazo2 == spminb2)){
            flag = flag^1;
        }
    }
}

void cerrar(void){
    if(flag){
        tempBrazo1++;
        if(tempBrazo1 == velb1){
            tempBrazo1 = 0;
            if(brazo1 > spminb1){
                brazo1--;
            }else{
                brazo1 = spminb1;
            }
        }
        tempBrazo2++;
        if(tempBrazo2 == velb2){
            tempBrazo2 = 0;
            if(brazo2 < spmaxb2){
                brazo2++;
            }else{
                brazo2 = spmaxb2;
            }
        }
        if((brazo1 == spminb1)&&(brazo2 == spmaxb2)){
            lineales = 50;
            flag = flag^1;
        }
    }
}

void fijos(char car){
    switch(car){
        case '1':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, AMBOS);
            movimientos(inst[0]);
            lineales = 90;
            //abrir();
            flag = 1;
            moveServo();
            break;
        case '2':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, VELOCIDAD);
            movimientos(inst[0]);
            lineales = 90;
            //abrir();
            moveServo();
            flag = 1;
            break;
        case '3':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, LUZ);
            movimientos(inst[0]);
            lineales = 90;
            //abrir();
            moveServo();
            flag = 1;
            break;
        case '4':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, DEFAULT);
            movimientos(inst[0]);
            moveServo();
            lineales = 90;
            //abrir();
            flag = 1;
            break;
        case '5':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, AMBOS);
            movimientos(inst[0]);
            //lineales = 50;
            cerrar();
            moveServo();
            break;
        case '6':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, VELOCIDAD);
            movimientos(inst[0]);
            //lineales = 50;
            cerrar();
            moveServo();
            break;
        case '7':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, LUZ);
            movimientos(inst[0]);
            //lineales = 50;
            cerrar();
            moveServo();
            break;
        case '8':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, DEFAULT);
            movimientos(inst[0]);
            //lineales = 50;
            moveServo();
            cerrar();
            break;
        case 'c':
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, blinking);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_4, GARRA_DEF);
            tempLuz++;
            if(tempLuz == 5000){
                blinking = 0x00;
            }else if(tempLuz == 10000){
                blinking = 0x04;
                tempLuz = 0;
            }
        default:
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, DEFAULT);
            movimientos(inst[0]);
            moveServo();
    }
}

/*-------------------------------------------------------------------------------------------------*/
/*----------------------------                MAIN                ---------------------------------*/
/*-------------------------------------------------------------------------------------------------*/
int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    IntMasterEnable();
    PinoutSet();
    configurePWM();
    configureUART();
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_4, 0x00);


    while(1){
        fijos(inst[1]);
    }
}
