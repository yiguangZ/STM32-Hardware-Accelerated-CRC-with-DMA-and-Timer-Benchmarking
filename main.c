/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "LED.h"
#include "CRC.h"
#include "UART.h"
#include <stdio.h>

/* Expected CRC Value */
#define uwExpectedCRCValue 0x5A60861E

static volatile uint32_t Software_ComputedCRC;

int main(void) {
	
	// Switch System Clock = 80 MHz
	System_Clock_Init(); 
	// TODO initialize modules
	SysTick_Init();
  UART2_Init();
	UART2_GPIO_Init();
  USART_Init(USART2);	
	LED_Init();
	printf("Starting CRC Calculation...\n");
	while(1) {
		LED_Toggle();
		// initialize CRC
		 uint32_t crc = INITIAL_CRC_VALUE;
		// start timer
		startTimer();
		// compute CRC
		for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
            crc = CrcSoftwareFunc(crc, DataBuffer[i], POLYNOME); 
        }
		// end timer
		uint32_t time = endTimer();
		// check CRC
		 if (crc != uwExpectedCRCValue) {
            LED_Off();
						break;
		 }
		// print time
		printf("CRC Calculation Time: %lu us\n", time);

		// delay
		 delay(1000);
	}
}