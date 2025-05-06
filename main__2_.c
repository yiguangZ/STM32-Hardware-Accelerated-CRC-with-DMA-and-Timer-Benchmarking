/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "LED.h"
#include "CRC.h"
#include "DMA.h"
#include "UART.h"
#include <stdio.h>

/* Expected CRC Value */
static uint32_t uwExpectedCRCValue = 0x5A60861E;	
static volatile uint32_t ComputedCRC;	
static volatile uint32_t ComputationDone = 0;	

void completeCRC(uint32_t crc){
	//TODO
	  ComputedCRC = crc; 
    ComputationDone = 1; 
}

int main(void) {
  	uint32_t time;
	
	// Switch System Clock = 80 MHz
	    System_Clock_Init();

	// systick init
	    SysTick_Init();

	// uart init
	    UART2_GPIO_Init();
    UART2_Init();
    USART_Init(USART2);

	// led, crc, dma init
	 LED_Init();

    // Initialize CRC
    CRC_Init();
    DMA_Init();

	while(1) {
		// TODO
	LED_Toggle();
	startTimer();
        ComputationDone = 0;
        CRC->CR |= CRC_CR_RESET;
        DMA1_Channel6->CNDTR = BUFFER_SIZE;  // Set number of data items to transfer
        DMA1_Channel6->CCR |= DMA_CCR_EN;   // Enable DMA channel
        while (!ComputationDone);
        DMA1_Channel6->CCR &= ~DMA_CCR_EN;
        time = endTimer();
  	if (ComputedCRC != uwExpectedCRCValue) {
            		LED_Off();
            		printf("CRC Mismatch: Computed = 0x%08X, Expected = 0x%08X\n", ComputedCRC, uwExpectedCRCValue);
           		 break;
        }
	printf("DMA-Based Hardware CRC Calculation Time: %lu us\n", time);
        delay(1000);



	}
  	while (1);
	
}


