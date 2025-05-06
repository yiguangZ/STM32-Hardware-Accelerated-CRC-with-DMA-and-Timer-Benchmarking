/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */
 
#include "DMA.h"
#include "CRC.h"

#include "DMA.h"
#include "stm32l476xx.h"

void DMA_Init(void) {
    //Enable the clock  DMA
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    //  Wait for DMA
    while (!(RCC->AHB1ENR & RCC_AHB1ENR_DMA1EN));

    // Disable channel
    DMA1_Channel6->CCR &= ~DMA_CCR_EN;

    // Set memory-to-memory mode
    DMA1_Channel6->CCR |= DMA_CCR_MEM2MEM;


    // Set the priority to high
    DMA1_Channel6->CCR |= DMA_CCR_PL_1;
    DMA1_Channel6->CCR &= ~DMA_CCR_PL_0;


    // Set peripheral size to 32 bits
    DMA1_Channel6->CCR |= DMA_CCR_PSIZE_1;
    DMA1_Channel6->CCR &= ~DMA_CCR_PSIZE_0;


    // Set memory to 32 bits
    DMA1_Channel6->CCR |= DMA_CCR_MSIZE_1;
    DMA1_Channel6->CCR &= ~DMA_CCR_MSIZE_0;


    // Disable peripheral increment mode
    DMA1_Channel6->CCR &= ~DMA_CCR_PINC;


    // Enable memory increment mode
    DMA1_Channel6->CCR |= DMA_CCR_MINC;


    // Disable circular mode
    DMA1_Channel6->CCR &= ~DMA_CCR_CIRC;


    // Set data transfer direction to memory-to-peripheral
    DMA1_Channel6->CCR |= DMA_CCR_DIR;


    // Set the data source
    DMA1_Channel6->CMAR = (uint32_t) DataBuffer;


    // Set the destination
    DMA1_Channel6->CPAR = (uint32_t) &(CRC->DR);


    // Disable half transfer interrupts
    DMA1_Channel6->CCR &= ~DMA_CCR_HTIE;


    // Disable transfer error interrupts
    DMA1_Channel6->CCR &= ~DMA_CCR_TEIE;


    // Enable transfer complete interrupts
    DMA1_Channel6->CCR |= DMA_CCR_TCIE;


    // Set interrupt priority to 0
    NVIC_SetPriority(DMA1_Channel6_IRQn, 0);


    // Enable the interrupt in NVIC
    NVIC_EnableIRQ(DMA1_Channel6_IRQn);

}


void DMA1_Channel6_IRQHandler(void) {   
    // Check Transfer Complete interrupt flag
    NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);
    if (DMA1->ISR & DMA_ISR_TCIF6) {
        // Clear the Transfer Complete interrupt flag
        DMA1->IFCR |= DMA_IFCR_CTCIF6;

        // Mark computation as completed
        completeCRC(CRC->DR);
    }

    // Clear global DMA interrupt flag 
    DMA1->IFCR |= DMA_IFCR_CGIF6;
}
