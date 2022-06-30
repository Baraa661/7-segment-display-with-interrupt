/*
 * interrupt.c
 *
 *  Created on: May 31, 2022
 *      Author: DELL
 */
#include "stm32f4xx.h"
#include "interrupt.h"
#include "gpio.h"

char current_index = 8;

char lookupTable_7Seg1[10][7]={{0,0,0,0,0,0,1},{1,0,0,1,1,1,1},{0,0,1,0,0,1,0},{0,0,0,0,1,1,0},{1,0,0,1,1,0,0},{0,1,0,0,1,0,0}
,{0,1,0,0,0,0,0},{0,0,0,1,1,1,1},{0,0,0,0,0,0,0},{0,0,0,0,1,0,0}};

void Interrupt_Init(GPIO_TypeDef * GPIOx, char Port , char pin , char enable)
{

	GPIO_Init (GPIOx,pin,0, enable);

	GPIOx->PUPDR |= (1u<< (2*pin));
	GPIOx->PUPDR &=~ (1u<< (2*pin+1));

	RCC->APB2ENR |= (1u<<14);

	EXTI->IMR |= (1u<<pin);
	EXTI->FTSR |= (1u<<pin);
	NVIC->ISER[0] |= (1u<<(6+pin));



	unsigned char temp;
	unsigned char cfg;
	if(pin>=0 && pin<=3)
	{
		temp = pin;
		cfg = 0;
	}else if(pin>=4 && pin<=7)
	{
		temp = pin-4;
		cfg = 1;
	}
	else if (pin>=8 && pin<=11)
	{
		temp = pin - 8;
		cfg =  2;
	}
	else if(pin>=12 && pin<=15)
	{
		temp = pin - 12;
		cfg = 3;
	}


	switch(Port)
	{
	case 'A':
		SYSCFG->EXTICR[cfg] &=~ (1u<<4*temp);
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
        break;
	case 'B':
		SYSCFG->EXTICR[cfg] |= (1u<<4*temp);
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
        break;
	case 'C':
		SYSCFG->EXTICR[cfg] &=~ (1u<<4*temp);
		SYSCFG->EXTICR[cfg] |= (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
		break;
	case 'D':
		SYSCFG->EXTICR[cfg] |= (1u<<4*temp);
		SYSCFG->EXTICR[cfg] |= (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
		break;
	case 'E':
		SYSCFG->EXTICR[cfg] &=~ (1u<<4*temp);
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] |= (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
		break;
	case 'H':
		SYSCFG->EXTICR[cfg] |= (1u<<4*temp);
		SYSCFG->EXTICR[cfg] |= (1u<<(4*temp+1));
		SYSCFG->EXTICR[cfg] |= (1u<<(4*temp+2));
		SYSCFG->EXTICR[cfg] &=~ (1u<<(4*temp+3));
		break;

	}
}

void Manage_7_seg(char add)
{
	current_index = current_index + add;



	switch(current_index){
		          case 0:
		        	    for(int i = 8; i<14; i++){
		        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[0][i-8]);
		        	    }
	//        			GPIO_Write(GPIOA,8,0);
	//        		    GPIO_Write(GPIOA,9,0);
	//        		    GPIO_Write(GPIOA,10,0);
	//        		    GPIO_Write(GPIOA,11,0);
	//        		    GPIO_Write(GPIOA,12,0);
	//        		    GPIO_Write(GPIOA,13,0);
	        		    GPIO_Write(GPIOA,15,1);
	        		    for(int j =0 ; j<500000;j++){}// delay for some time
	        		    break;
	        		case 1:
	        			for(int i = 8; i<14; i++){
	        				        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[1][i-8]);
	        				        	    }
	        		    GPIO_Write(GPIOA,15,1);
	        		    for(int j =0 ; j<500000;j++){}// delay for some time
	        		    break;
	        		case 2:
	        			for(int i = 8; i<14; i++){
	        				        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[2][i-8]);
	        				        	    }
						GPIO_Write(GPIOA,15,0);

						for(int j =0 ; j<500000;j++){}// delay for some time
						break;
					case 3:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[3][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);

						for(int j =0 ; j<500000;j++){}// delay for some time
						break;
					case 4:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[4][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);

						for(int j =0 ; j<500000;j++){}// delay
						break;
					case 5:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[5][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);

						for(int j =0 ; j<500000;j++){}// delay
						break;
					case 6:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[6][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);
						for(int j =0 ; j<500000;j++){}// delay for some time
						break;
					case 7:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[7][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,1);
						for(int j =0 ; j<500000;j++){}// delay for some time
						break;
					case 8:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[8][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);
						for(int j =0 ; j<500000;j++){}// delay for some time
						break;
					case 9:
						for(int i = 8; i<14; i++){
							        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg1[9][i-8]);
							        	    }
						GPIO_Write(GPIOA,15,0);

						for(int j =0 ; j<500000;j++){}// delay for some time
						break;

		}

}
