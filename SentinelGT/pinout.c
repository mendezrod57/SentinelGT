//*****************************************************************************
//
// Configure the device pins for different signals
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 9/3/2018 at 00:52:15
// by TI PinMux version 4.0.1511 
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "pinout.h"

//*****************************************************************************
//
//! \addtogroup pinout_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Configures the device pins for the customer specific usage.
//!
//! \return None.
//
//*****************************************************************************
void
PinoutSet(void)
{
    //
    // Enable Peripheral Clocks 
    //
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	/*********** MOTOR *********************/
    //
    // Configure the GPIO Pin Mux for PC7
	// for GPIO_PC7
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    //
    // Configure the GPIO Pin Mux for PC6
	// for GPIO_PC6
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);

    //
    // Configure the GPIO Pin Mux for PC5
	// for GPIO_PC5
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PC4
	// for GPIO_PC4
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
	/*********** pinza *********************/
    //
    // Configure the GPIO Pin Mux for PF2
	// for GPIO_PF2
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //
    // Configure the GPIO Pin Mux for PF3
	// for GPIO_PF3
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	/*********** LUZ *********************/
    //
    // Configure the GPIO Pin Mux for PA2
	// for GPIO_PA2
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);
	/*********** VELOCIDAD *********************/
    //
    // Configure the GPIO Pin Mux for PA3
	// for GPIO_PA3
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);

    //
    // Configure the GPIO Pin Mux for PE4
	// for M0PWM4
    //
	MAP_GPIOPinConfigure(GPIO_PE4_M0PWM4);
	MAP_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PB5
	// for M0PWM3
    //
	MAP_GPIOPinConfigure(GPIO_PB5_M0PWM3);
	MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PD1
	// for M0PWM7
    //
	MAP_GPIOPinConfigure(GPIO_PD1_M0PWM7);
	MAP_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

    //
    // Configure the GPIO Pin Mux for PB4
	// for M0PWM2
    //
	MAP_GPIOPinConfigure(GPIO_PB4_M0PWM2);
	MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PE5
	// for M0PWM5
    //
	MAP_GPIOPinConfigure(GPIO_PE5_M0PWM5);
	MAP_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PA0
	// for U0RX
    //
	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PA1
	// for U0TX
    //
	MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);

}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

