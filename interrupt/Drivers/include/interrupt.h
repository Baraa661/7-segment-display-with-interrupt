/*
 * interrupt.h
 *
 *  Created on: May 31, 2022
 *      Author: DELL
 */

#ifndef INCLUDE_INTERRUPT_H_
#define INCLUDE_INTERRUPT_H_

void Interrupt_Init(GPIO_TypeDef * GPIOx, char Port , char pin , char enable);
void Manage_7_seg(char add);

#endif /* INCLUDE_INTERRUPT_H_ */
