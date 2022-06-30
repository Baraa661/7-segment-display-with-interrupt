#include<stdint.h>
#include "stm32f4xx.h"
#include "gpio.h"
#include "interrupt.h"

void ISR_OF_EXTI0(void);
void ISR_OF_EXTI1(void);

int main(void)
{

	for(int j = 8; j<14; j++)
			 {
				 GPIO_Init(GPIOA,j,1,0);
			 }

	GPIO_Init(GPIOA,15,1,0);

	Interrupt_Init(GPIOB, 'B' ,0 , 1);
	Interrupt_Init(GPIOB, 'B' ,1 , 1);
//	void Manage_7_seg(char add);

	// super loop


	while(1)
	{

	}

}

void ISR_OF_EXTI0(void)
{
	Manage_7_seg(1);
}

void EXTI0_IRQHandler(void) {
    NVIC->ICER[0]|=(1u<<7);
	ISR_OF_EXTI0();
	NVIC->ISER[0]|=(1u<<7);

}

void ISR_OF_EXTI1(void)
{
	Manage_7_seg(-1);


}

void EXTI1_IRQHandler(void) {
    NVIC->ICER[0]|=(1u<<6);
	ISR_OF_EXTI1();
	NVIC->ISER[0]|=(1u<<6);

}
