/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6A
 */

#include "SysTimer.h"

static uint32_t volatile step;

void SysTick_Init(void) {
	// SysTick Control & Status Register
	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick Counter
	
	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Select clock source
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	// TODO
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	
	// Configure and Enable SysTick interrupt in NVIC
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 1); // Set Priority to 1
}

void SysTick_Handler(void) {
	//TODO
		++step;
}

void delay(uint32_t ms) {
    // Reset the counter
    step = 0;

    // Reset the SysTick counter
    SysTick->VAL = 0;

    // Set SysTick LOAD value for 1 ms interrupts
    SysTick->LOAD = (80 * 1000) - 1; // 80 MHz / 1 kHz = 80,000 

    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    // Busy wait until the required delay has elapsed
    while (step < ms);

    // Disable SysTick
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
void startTimer(void) {
    // Reset the counter
    step = 0;

    // Reset the SysTick counter
    SysTick->VAL = 0;

    // Set SysTick LOAD value for max
    SysTick->LOAD = 0xFFFFFF;

    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

uint32_t endTimer(void) {
    // Disable the counter
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;


    // Return the time
    return (0xFFFFFF - SysTick->VAL) / 80;
}
