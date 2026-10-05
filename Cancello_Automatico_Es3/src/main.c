/*
 * main.c
 *
 *  Created on: 22 ott 2023
 *      Author: massimo
 */

//Sistema di controllo di un cancello automatico

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>

#define TA 8
#define TC 20

enum{
	IDLE, OPENING, CLOSING, WAITING
};

int timeout = 0, waiting_time = 0;
int state = IDLE;


void print_state(int);


void setup(){

	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);	//LED ROSSO
	GPIO_config_input(GPIOB, 10);	//pulsante X
	GPIO_config_input(GPIOB, 4);	//pulsante Y
	GPIO_config_input(GPIOB, 5);	//pulsante Z

	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 5000);

	TIM_set(TIM2, 0); //resetta il timer
	TIM_on(TIM2);

	//TIM_enable_irq(TIM2, IRQ_UPDATE);
}


void print_state(int t){
	if (t < 5)
		DISPLAY_puts(0, "----");
	else if (t < 10)
	    DISPLAY_puts(0, "--- ");
	else if (t < 15)
	    DISPLAY_puts(0, "-- ");
	else if (t < 19)
		DISPLAY_puts(0, "-  ");
	else
	    DISPLAY_puts(0, "   ");
}



void loop(void){

	char s[5];

	switch(state){

		case IDLE:{

			GPIO_write(GPIOB, 0, 0);
			strcpy(s, "----");
			DISPLAY_puts(0, s);

		break;
		}

		case OPENING:{

			//DISPLAY_puts

			if(TIM_update_check(TIM2)){

				GPIO_toggle(GPIOB, 0);
				timeout++;

				print_state(timeout);

				if(timeout >= TC){
					state = WAITING;
					waiting_time = 0;
				}
				TIM_update_clear(TIM2);
			}

			break;
			}

			case WAITING:{

				if(TIM_update_check(TIM2)){

					GPIO_toggle(GPIOB, 0);
					waiting_time++;

					//sprintf(s, "%4d", (int)waiting_time);
					//DISPLAY_puts(0, s);
					DISPLAY_puts(0, "    ");

					if(waiting_time >= TA){
						state = CLOSING;
						waiting_time = 0;
					}

					TIM_update_clear(TIM2);
				}

			break;
			}

			case CLOSING:{

				if(TIM_update_check(TIM2)){

					GPIO_toggle(GPIOB, 0);
					timeout--;

					print_state(timeout);

					if(timeout < 0){
						state = IDLE;
					}

					TIM_update_clear(TIM2);
				}

			break;
			}
		}
}


//TASTO X
	void EXTI15_10_IRQHandler(void){
	if(EXTI_isset(EXTI10)){

		switch(state){
		case IDLE:{
			state = OPENING;
			timeout = 0;
			break;
		}

		case CLOSING:{
			state = OPENING;
			waiting_time = 0;
			break;
		}
	}

	EXTI_clear(EXTI10);
	}
}


//Tasto Y
void EXTI4_IRQHandler(void){
	if(EXTI_isset(EXTI4)){
		if(state == WAITING){
			state = CLOSING;
			waiting_time = 0;
		}

		EXTI_clear(EXTI4);
	}
}


//TASTO Z
void EXTI9_5_IRQHandler(void){
	if(EXTI_isset(EXTI5)){
		switch(state){

		case CLOSING:{
			state = OPENING;
			break;
		}

		case WAITING:{
			state = WAITING;
			waiting_time = 0;
			break;
		}
	}

	EXTI_clear(EXTI5);
	}
}


int main(int argc, char **argv){

	setup();

	//infinite loop
	for(;;){

		loop();
	}

	return 0;
}
