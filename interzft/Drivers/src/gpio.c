#include "stm32f4xx.h"
#include "gpio.h"

void GPIO_Init (GPIO_TypeDef * GPIOx,char pin,char dir,char enable_pin)
{
	//Enable clock to GBIOx
	RCC->AHB1ENR |= (1u<<enable_pin);

	if(dir)
	{
		GPIOx->MODER |= (1u<<(2*pin));
		GPIOx->MODER &=~(1u<<(2*pin+1));
	}
	else
	{
		GPIOx->MODER &=~(1u<<(2*pin));
		GPIOx->MODER &=~(1u<<(2*pin+1));
	}

}

char GPIO_Write(GPIO_TypeDef * GPIOx,char pin,char state)
{
	if (GPIOx->MODER & (1u<<(2*pin)))
	{
		if(state)
			{
				GPIOx->ODR |=(1u<<pin);
			}
			else
			{
				GPIOx->ODR &=~(1u<<pin);
			}
		return 0;
	}
	else
	{
		return 1;
	}
}


char GPIO_Read(GPIO_TypeDef * GPIOx,char pin)
{

	if (!(GPIOx->MODER & (1u<<(2*pin))))
	{  // set input pin to pull up down
		GPIOx ->PUPDR |= (1u<<(2*pin));
		GPIOx ->PUPDR &=~ (1u<<(2*pin+1));
		int y ;
		y =GPIOx ->IDR & (1<<pin);
		if (y==0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
}


