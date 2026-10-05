/*
 * main.c
 *
 *  Created on: 31 ott 2023
 *      Author: massimo
 */
#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>
#define DIM 5

enum{
	IDLE,
	PRE_CLOSING,
	CLOSING,
	OPENING,
	MOVE
};

int state = IDLE;
int curr_floor = 0;
int dest_floor = 2;
int flashing_counter = 0;
int tick_counter = 0;

int wait_time = 0;
int elevator_speed = 0;

void setup(){

	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_init(GPIOC);

	//Led
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOC, 2);
	GPIO_config_output(GPIOC, 3);
	GPIO_config_output(GPIOB, 8);

	//Pulsante X
	GPIO_config_input(GPIOB, 10);
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	//Pulsante Y
	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	//Pulsante Z
	GPIO_config_input(GPIOB, 5);
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	//configurazione timer
	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 1250);

	TIM_set(TIM2, 0); //resetta il counter
	TIM_on(TIM2);

	TIM_enable_irq(TIM2, IRQ_UPDATE);

	//configurazione ADC
	ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);

	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_channel_config(ADC1, GPIOC, 1, 11);

	ADC_on(ADC1); //accende la periferica, l'elettronica
}


//char visualize(void){
//	return (curr_floor % 2) == 0 ? ' ' : '-';
//}


void print_floor(char *str){

	if(curr_floor % 2 == 1){
		sprintf(str, "%4d", curr_floor);
		strcat(str, "-");
		DISPLAY_puts(0, str);
	}
	else{
		sprintf(str, "%4d", curr_floor);
		DISPLAY_puts(0, str);
	}
}



//ISR pulsante X
void EXTI15_10_IRQHandler(void){

	if(EXTI_isset(EXTI10)){
		if(state == IDLE){
			if(dest_floor != curr_floor){
				state = PRE_CLOSING;
				curr_floor = dest_floor;
			}
		}
		EXTI_clear(EXTI10);
	}
}


//ISR pulsante Y
void EXTI4_IRQHandler(void){

	if(EXTI_isset(EXTI4)){
		dest_floor = 1;

		if(dest_floor != curr_floor){
			state = PRE_CLOSING;
			curr_floor = dest_floor;
		}
		EXTI_clear(EXTI4);
	}
}


//ISR pulsante Z
void EXTI19_5_IRQHandler(void){

	if(EXTI_isset(EXTI5)){
		dest_floor = 0;

		if(dest_floor != curr_floor){
			state = PRE_CLOSING;
			curr_floor = dest_floor;
		}

		EXTI_clear(EXTI5);
	}
}


void TIM2_IRQHandler(void){

	if(TIM_update_check(TIM2)){

		switch(state){

		case PRE_CLOSING:{

			tick_counter++;
			if(tick_counter >= wait_time){
				tick_counter = 0;
				state = CLOSING;
			}
			break;
		}

		case CLOSING:{

			flashing_counter++;
			if(flashing_counter >= 2){
				GPIO_toggle(GPIOC, 2);
				flashing_counter = 0;
			}

			tick_counter++;
			if(tick_counter >= 12){
				GPIO_write(GPIOC, 2, 0);
				tick_counter = 0;
				flashing_counter = 0;
				state = MOVE;
			}
			break;
		}

		case MOVE:{

			//simulazione corsa ascensore

			flashing_counter++;
			if(flashing_counter >= 2){
				GPIO_toggle(GPIOB, 0);
				flashing_counter = 0;
			}

			tick_counter++;
			if(tick_counter >= elevator_speed){
				GPIO_write(GPIOB, 0, 0);
				state = OPENING;
				tick_counter = 0;
			}

			break;
		}

		case OPENING:{

			flashing_counter++;
			if(flashing_counter >= 2){
				GPIO_toggle(GPIOC, 3);
				flashing_counter = 0;
			}

			tick_counter++;
			if(tick_counter >= 12){
				GPIO_write(GPIOC, 3, 0);
				tick_counter = 0;
				state = IDLE;
			}
			break;
		}

		}
		TIM_update_clear(TIM2);
	}
}


int main(int argc, char **argv){

	setup();
	char s[DIM];

	for(;;){

		ADC_sample_channel(ADC1, 10);
		ADC_start(ADC1);
		while(!ADC_completed(ADC1)){}

		//[0, 63] --> [0.5, 3]
		DISPLAY_dp(2, 1); //punto decimale on

		int time_steps = ADC_read(ADC1) * 10.0 / 63;
		float time = time_steps * 0.25 + 0.5;
		sprintf(s, "%4d", (int)time * 10);
		DISPLAY_puts(0, s);

		wait_time = (time / 2) / 0.125;

		ADC_sample_channel(ADC1, 11);
		ADC_start(ADC1);
		while(!ADC_completed(ADC1)){}

	 	int spd_steps = ADC_read(ADC1) * 7.0 / 63;
		float speed = spd_steps * 0.25 + 0.25;
		//sprintf(s, "%4d", (int)(speed * 10));
		//DISPLAY_puts(0, s);
		//DISPLAY_dp(2, 1); //punto decimale on

		elevator_speed = (speed / 2) / 0.125;

		//print_floor(s);

	}

	return 0;
}

/*
 *
 * opening_time = closing_time => timing = 1.5
 *
 * 250ms = 0.25s => tempistica di lampeggio dei LED verde, rosso e giallo
 *
 * 1500ms = 1.5s = 6 periodi
 * led flashing 250ms = 1 periodo
 *
 *
 * provare parametro PSC 42000 per avere un incremento diverso
 * dividere per un fattore 10? perchè? Devo capirlo.
 *
 *
 * AN11: tempo di partenza, regolabile nell'intervallo [0.5, 3] secondi,
 * con risoluzione di 250ms
 *
 * AN10: velocita' di marcia regolabile nell'intervallo [0.25, 2]
 * piani/secondo, con risoluzione di 250ms
 *
 *
 * ragionamento tempistiche
 *
 * 250ms
 * 1.5s
 * 3.0s - 0.5s -> 2.5s = 2500ms
 * 2s/piano - 0.25s/piano
 *
 * 125ms => 2 periodi flashing
 * 1.5s = 1500ms => 12 periodi
 * [500ms , 3000ms] => 20 periodi al max da 125ms
 * faccio un piano ogni 250ms
 *
 * considerazioni per t_start [0.5s, 3.0s]
 *
 * 0.5s             0
 * 0.75s            1
 * 1.0s             2
 * 1.25s            3
 * 1.5s             4
 * 1.75s            5
 * 2.0s             6
 * 2.25s            7
 * 2.5s             8
 * 2.75s            9
 * 3.0s             10
 *
 * 11 possibili valori quindi
 *
 * considerazioni sulla velocita
 *
 * impostazioni velocita che possono essere consentite
 * 0.25s/piano       0
 * 0.50s/piano       1
 * 0.75s/piano       2
 * 1.0s/piano        3
 * 1.25s/piano       4
 * 1.50s/piano       5
 * 1.75s/piano       6
 * 2.0s/piano        7
 *
 * 8 valori possibili  => Vmax = 8
 *
 * la nostra granularità del timer però è 125ms quindi
 *
 * tirare fuori il numero di periodi.
 *
 * 0.25s/piano       0            0.125 s/piano      2.5 ->(0.25piani/s *10)
 * 0.50s/piano       1            0.25  s/piano      5
 * 0.75s/piano       2            0.375 s/piano      7.5
 * 1.0s/piano        3            0.5   s/piano      10
 * 1.25s/piano       4            0.625 s/piano      12.5
 * 1.50s/piano       5            0.75  s/piano      15
 * 1.75s/piano       6            0.875 s/piano      17.5
 * 2.0s/piano        7            1.0   s/piano      20
 *
 *
 * l'ampiezza dell'intervallo è 1.75s/piani
 *
 * */
