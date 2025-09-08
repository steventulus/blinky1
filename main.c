#include <stdint.h>

#define PERIPH_BASE     0x40000000UL
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000UL)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x20000UL)

#define RCC_BASE        (AHBPERIPH_BASE + 0x1000UL)
#define GPIOC_BASE      (APB2PERIPH_BASE + 0x1000UL)

#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define RCC_APB2ENR_IOPCEN (1 << 4)

void delay(volatile unsigned int count) {
    while (count--) __asm__("nop");
}

int main(void) {
    
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    
    GPIOC_CRH &= ~(0xF << 20);  
    GPIOC_CRH |=  (0x1 << 20);  

    while (1) {
        GPIOC_ODR &= ~(1 << 13); 
        delay(50000);
        GPIOC_ODR |=  (1 << 13); 
        delay(500000);
    }
}

