#include <stdio.h>
#include <stdlib.h>

#define RCC_APB2ENR  (*( ( volatile unsigned int * )0x40021018 ) ) 
#define GPIOC_CRH  (*( ( volatile unsigned int * )0x40011004 ) ) 
#define GPIOC_BSRR  (*( ( volatile unsigned int * )0x40011010 ) ) 

#define GPIOC_PERH_ADDR 0x40011000
#define ODR_ADDR_OFF 0xc

// Define base address of peripheral bit-band
#define BITBAND_PERI_BASE 0x40000000
// Define base address of peripheral alias band
#define ALIAS_PERI_BASE 0x42000000
// Convert PERI address to alias region
#define BITBAND_PERI(a,b) ((ALIAS_PERI_BASE + ((uint32_t)a-BITBAND_PERI_BASE)*32 + (b*4)))






int main(){


    uint32_t *GPIOC_ODR = GPIOC_PERH_ADDR + ODR_ADDR_OFF;
    uint32_t *GPIOC_PIN13 = BITBAND_PERI(GPIOC_ODR, 13);

    *GPIOC_PIN13 = 0x1; // Turns GPIO HIGH
    
    // Using varibles:
    // int volatile * const RCC_APB2ENR = (int *) 0x40021018;
    // int volatile * const GPIOC_CRH = (int *) 0x40011004;
    // int volatile * const GPIOC_BSRR = (int *) 0x40011010;
    // *RCC_APB2ENR |= (1<<4);   // Enable GPIOC Clock
    // *GPIOC_CRH &= ~(0xF<<20); // Clear Bits 23:22:21:20
    // *GPIOC_CRH |= (0x11<<20); // PC13 Output mode 50 MHz, push pull
    // *GPIOC_BSRR |= (1<<13);   // Set the pin PC13
    // *GPIOC_BSRR |= (1<<29);   // RESET the pin PC13


    // Using defines:
    RCC_APB2ENR |= (1<<4);   // Enable GPIOC Clock
    GPIOC_CRH &= ~(0xF<<20); // Clear Bits 23:22:21:20
    GPIOC_CRH |= (0x11<<20); // PC13 Output mode 50 MHz, push pull
    GPIOC_BSRR |= (1<<13);   // Set the pin PC13
    GPIOC_BSRR |= (1<<29);   // RESET the pin PC13




    int x  = 1000000;

    while(1){
        while(x>1){x--;}
        x = 200000;
        // GPIOC_BSRR |= (1<<13);  // Set the pin PC13
        *GPIOC_PIN13 = 0x1; // Turns GPIO HIGH
        while(x>1){x--;}
        x = 200000;
        // GPIOC_BSRR |= (1<<29);  // RESET the pin PC13
        *GPIOC_PIN13 = 0x0; // Turns GPIO LOW
    }

    return 0;
}
