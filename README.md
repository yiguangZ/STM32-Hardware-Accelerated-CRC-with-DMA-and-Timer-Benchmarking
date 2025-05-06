# ⚙️ STM32 CRC Benchmarking with Software, Hardware, and DMA (ECE 153B Labs 6A–6C)

This embedded systems project explores three implementations of CRC32 computation on the STM32L476 microcontroller. Each lab builds progressively from software-based CRC to hardware-accelerated CRC and finally to DMA-assisted CRC, allowing performance comparisons in execution time and system efficiency.

## 🔍 Overview

| Lab  | CRC Method         | Description                                                                 |
|------|--------------------|-----------------------------------------------------------------------------|
| 6A   | Software CRC       | Pure C implementation using bitwise operations, timing measured with SysTick. |
| 6B   | Hardware CRC       | Uses STM32 CRC peripheral to compute CRC directly from data buffer.         |
| 6C   | DMA + Hardware CRC | Employs DMA to transfer buffer data to CRC peripheral, minimizing CPU load. |

## 🧰 Features

- Custom software CRC implementation with adjustable polynomial
- Hardware CRC configuration via STM32 peripheral registers
- DMA initialization and ISR handling for automated CRC transfer
- Time benchmarking using the SysTick timer
- UART-based printf debugging via USART2
- LED signaling for success/failure indicators

## 📁 File Structure

- `main.c`: Software CRC implementation (Lab 6A)
- `main__1_.c`: Hardware CRC implementation (Lab 6B)
- `main__2_.c`: DMA-based CRC implementation (Lab 6C)
- `CRC.c`, `CRC__1_.c`: CRC computation logic
- `DMA.c`: DMA setup and interrupt handling
- `SysTimer.c`: SysTick benchmarking utilities
- `UART.c`: USART initialization and communication
- `LED.c`: GPIO setup for onboard LED

## 📦 Dependencies

- STM32 HAL headers (e.g., `stm32l476xx.h`)
- CMSIS-compliant toolchain (STM32CubeIDE, Keil MDK, or GCC with Make)

## 🚀 How to Run

1. Flash each `main*.c` variant to the STM32L476 board separately.
2. Open a UART terminal (9600 baud) to monitor CRC computation timing.
3. Observe LED behavior:
   - Toggled LED: success
   - LED off: CRC mismatch
4. Compare timing results across versions to evaluate performance gains.

## 🖥️ Hardware Setup

- STM32L476 Discovery board
- USB-UART cable (USART2 on PA2/PA3)
- Onboard green LED (PA5) for visual feedback

## 👤 Author

Yiguang Zhu — ECE 153B Lab Series (Winter 2024)
