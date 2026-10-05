/*
 * main.c
 *
 *  Created on: 16 mag 2026
 *      Author: codewalker23
 */

#include "stm32_unict_lib.h"
#include "stdio.h"

enum alarms{
	ALM1,
	ALM2,
	ALM3,
	ALM4
};

typedef enum{
	IDLE,
	ON,
	SETUP
}states;

volatile int count = 0;
volatile states state = IDLE;

void config(){

	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOC, 2);
	GPIO_config_output(GPIOC, 3);

	GPIO_config_input(GPIOB, 5);
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	GPIO_config_input(GPIOB, 6);
	GPIO_config_EXTI(GPIOB, EXTI6);
	EXTI_enable(EXTI6, FALLING_EDGE);

	DISPLAY_init();

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 41999, 1999); //1 secondo acceso e 1 secondo spento
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_set(TIM2, 0);
	TIM_on(TIM2);

	CONSOLE_init();
}


void TIM2_IRQHandler(void){
	if(TIM_update_check(TIM2)){
		GPIO_toggle(GPIOC, 2);
		count += 1;
	TIM_update_clear(TIM2);
	}
}

//implementare ISR dove premendo il pulsante accendi il led verde e se lo ripremi lo spegni
void EXTI9_5_IRQHandler(void){
	if(EXTI_isset(EXTI5)){
		if(GPIO_read(GPIOC, 3) == 1)
			GPIO_write(GPIOC, 3, 0);
		else
			GPIO_write(GPIOC, 3, 1);
		EXTI_clear(EXTI5);
	}

	if(EXTI_isset(EXTI6)){
		if(state == IDLE)
			state = SETUP;
		else
			state = IDLE;
		EXTI_clear(EXTI6);
	}
}

void EXTI4_IRQHandler(void){
	if(EXTI_isset(EXTI4)){

		switch(state){

		case IDLE:{
			state = ON;
			break;
		}

		case ON:
			state = ON;
			count = 0;
			break;
		}
		EXTI_clear(EXTI4);
	}
}


int main(void){

    ClockConfig();
	config();
	char s[5];
	sprintf(s, "%4d", count);

	for(;;){

		//DISPLAY_dp(1, 1);

		switch(state){

		case IDLE: {
			DISPLAY_puts(0, "OFF ");
			count = 0;
			GPIO_write(GPIOB, 0, 0);
			break;
		}

		case ON:{
			DISPLAY_puts(0, "ON  ");
			GPIO_write(GPIOB, 0, 1);

			if(count == 10)
				state = IDLE;
			break;
		}

		case SETUP: {
			DISPLAY_puts(0, s);
			break;
		}

		}
	}
}

//utilizzare il DMA per trasferimento dati da periferica a Memoria
