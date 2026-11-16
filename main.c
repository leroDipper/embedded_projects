#include <stdint.h>
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830)
#define GPIOD_MODER (*(volatile uint32_t *)0x40020C00)
#define GPIOD_ODR  (*(volatile uint32_t *)0x40020C14)
#define STK_BASE  0xE000E010
#define STK_CTRL  (*(volatile uint32_t *)(STK_BASE + 0x00))
#define STK_LOAD  (*(volatile uint32_t *)(STK_BASE + 0x04))
#define STK_VAL   (*(volatile uint32_t *)(STK_BASE + 0x08))


void systick_init();
void delay_ms(uint32_t ms);


int main(void) {

systick_init();
RCC_AHB1ENR |= (1 << 3);

GPIOD_MODER &= ~(1 << 24);

GPIOD_MODER &= ~(1 << 25);

GPIOD_MODER |= (1 << 24);

while (1) {
    delay_ms(500);
    GPIOD_ODR ^= (1 << 12);   // this ^ is correct: XOR flips the bit
}
}

void delay_ms(uint32_t ms) {
    uint32_t cycles = 0;
    while (cycles < ms) {
        if (STK_CTRL & (1 << 16)) {
            cycles = cycles + 1;
        }
    }
}

void systick_init(){
    STK_CTRL = 0;
    STK_LOAD = 16000 - 1;
    STK_VAL = 0;
    STK_CTRL = (1 << 2) | (1 << 0);   // processor clock + enable, no interrupt
}
