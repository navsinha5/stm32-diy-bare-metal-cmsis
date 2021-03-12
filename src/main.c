#include "led.h"
#include "usart1.h"
#include "tim1.h"
#include "stm32f1xx.h"


int main(void){
    /* set HSE as system clock source */
    RCC->CR |= RCC_CR_HSEON;
    RCC->CFGR |= RCC_CFGR_SW_HSE;

    initUsart();
    ledInit();
    tim1Init();
    counterInit(2000);
    while(1);
}


/* TIM1 Update Interrupt Handler */
void TIM1_UP_IRQHandler(void){
    // toggle(); // this works
    GPIOC->ODR ^= GPIO_ODR_ODR13; // this doesn't
    /* clear the update interrupt flag */
    TIM1->SR &= ~ TIM_SR_UIF;
}


/* USART1 global interrupt handler implementation */
void USART1_IRQHandler(void){
    /* check if data is available to read */
    if(USART1->SR & USART_SR_RXNE){
        uint8_t value = USART1->DR;
        switch(value){
            case 'a':
                counterInit(200);
                break;
            
            case 'b':
                counterInit(500);
                break;

            case 'c':
                counterInit(1000);
                break;

            default:
                break;
        }
        send(value);
    }
}