#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

void _GPIO_Init(void);
void _EXTI_Init(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

void main(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    //_GPIO_Init();
    
    while (1) {
        /*
        GPIOA->ODR |= 0x00000001;
        DelayMS(100);
        GPIOA->ODR &= 0x00000000;
        DelayMS(100);
        */
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, 1);
        DelayMS(100);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, 0);
        DelayMS(100);
    }
}

void _GPIO_Init(void) {
    RCC->APB2ENR |=  0x00000004;
	
    GPIOA->CRL &= 0x44444400;
    GPIOA->CRL |= 0x00000033;
}

void _EXTI_Init(void) {
    RCC->APB2ENR |= 0x0000001C;
    GPIOB->CRL &= 0x44444440;
    GPIOB->CRL |= 0x00000009;
            
    AFIO->EXTICR[1] |= 0x0001;
            
    EXTI->IMR |= 0x00000020;
    EXTI->FTSR |= 0x00000020;
    NVIC->ISER[1] |= 0x00000040;
}

void DelayMS(unsigned short wMS) {
    register unsigned short i;
    for (i=0; i<wMS; i++)
        DelayUS(1000);
}

void DelayUS(unsigned short wUS) {
    volatile int Dly = (int)wUS*17;
    for(; Dly; Dly--);
}
