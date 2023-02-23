#include <stm32f10x.h>

void _GPIO_Init(void);

void main(void) {
    _GPIO_Init();
    
    while (1) {
        
    }
}

void _GPIO_Init(void) {
	RCC->APB2ENR |= 0x00000000;
}
