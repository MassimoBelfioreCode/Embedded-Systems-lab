/*
 * main.c
 *
 *  Created on: 13 nov 2023
 *      Author: massimo
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM 30

enum {
	DIS,
	PRE_ATT,
	PRE_ATT_OK,
	ATT,
	PRE,
	ATT_OK,
	ALL,
	SETP
};

/*il professore anzichè tenere tutte le variabili globali qui
 * disordinate le incapsula in una struct e poi quando gli serve
 * quella variabile globale ci accede come campo della struct,
 * questo viene fatto per una questione di eleganza e leggibilità
*/

int state = DIS;
char pwd[DIM] = "1234";

typedef struct{
	int tick_counter;
	int exit_time;
	int enter_time;
} times;

times timing;


void config(){

	CONSOLE_init();
	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_init(GPIOC);

	GPIO_config_output(GPIOC, 3);
	GPIO_config_output(GPIOC, 2);
	GPIO_config_output(GPIOB, 0);

	GPIO_config_input(GPIOB, 10);
	GPIO_config_input(GPIOB, 4);
	GPIO_config_input(GPIOB, 5);
//#ifdef zzzz
	//tasto X
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	//tasto Y
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	//tasto Z
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 2000);

	TIM_set(TIM2, 0);
	TIM_on(TIM2);

	TIM_enable_irq(TIM2, IRQ_UPDATE);

//#endif
	printf("Started\n");
}


void getstring(char *s, int maxlen)
{
	int i = 0;
	for (;;) {
		char c = readchar();
		if (c == 13) {
			printf("\n");
			s[i] = 0;
			return;
		}
		else if (c == 8) {
			if (i > 0) {
				--i;
				__io_putchar(8); // BS
				__io_putchar(' '); // SPAZIO
				__io_putchar(8); // BS
			}
		}
		else if (c >= 32) { // il carattere appartiene al set stampabile
			if (i < maxlen) {
				__io_putchar(c); // echo del carattere appena inserito
				// inserisci il carattere nella stringa
				s[i] = c;
				i++;
			}
		}
	}
}


char ask_pwd(){
	char s[DIM];
	printf("INSERT THE PASSWORD: ");
	fflush(stdout);
	getstring(s, DIM);

	if(strcmp(pwd, s) == 0)
		return 1;

	printf("PASSWORD ERROR: ");
	fflush(stdout);
	printf("\n");
	return 0;
}


void check_pwd(){

	for(int i = 0; i < 3; i++){
		if(ask_pwd()){
			state = DIS;
			break;
		}
	}

	if(state != DIS)
		state = ALL;
}


void show_state(){

	switch(state){

	case DIS:
		DISPLAY_puts(0, "ATT ");
		break;

	case PRE:
		DISPLAY_puts(0, "Pre ");
		break;

	case PRE_ATT:
		DISPLAY_puts(0, "Patt");
		break;

	case ATT:
		DISPLAY_puts(0, "Att ");
		break;

	case ALL:
		DISPLAY_puts(0, "ALL ");
		break;

	case SETP:
		DISPLAY_puts(0, "SET ");
		break;

	}
}

/*
void settings(char *str){

	getstring(str, DIM);

	if(strcmp(str, "PASSWORD") == 0){
		printf("INSERT NEW PASSWORD: ");
		fflush(stdout);
		getstring(str, DIM);
		strncpy(pwd, str, DIM);
	}
	if(strcmp(str, "OUT-TIME") == 0){
		printf("INSERT NEW OUT-TIME: ");
		fflush(stdout);
		getstring(str, DIM);
		exit_time = atoi(str);
	}
	if(strcmp(str, "IN-TIME") == 0){
		printf("INSERT NEW IN-TIME: ");
		fflush(stdout);
		getstring(str, DIM);
		enter_time = atoi(str);
	}
	if(strcmp(str, "EXIT") == 0){
		state = DIS;
	}
}
*/

void settings(char *str){

	char token[DIM];
	token[DIM] = '\0';
	getstring(str, DIM);

	strncpy(token, strtok(str, " "), DIM);

	if(strcmp(token, "PASSWORD") == 0){
		strncpy(token, strtok(NULL, " "), DIM);
		strncpy(pwd, token, DIM);
	}
	else if(strcmp(token, "OUT-TIME") == 0){
		strncpy(token, strtok(NULL, " "), DIM);
		timing.exit_time = atoi(token);
	}
	else if(strcmp(token, "IN-TIME") == 0){
		strncpy(token, strtok(NULL, " "), DIM);
		timing.enter_time = atoi(token);
	}
	else if(strcmp(token, "EXIT") == 0){
		state = DIS;
	}
	else
		printf("Error\n");
}


void EXTI15_10_IRQHandler(void){ //pulsante di attivazione allarme
	if(EXTI_isset(EXTI10)){
		if(state == DIS){
			state = PRE_ATT_OK;
		}
		EXTI_clear(EXTI10);
	}
}


void EXTI9_5_IRQHandler(void){ //pulsante che simula l'attivazione del sensore di rilevamento di intrusione
	if(EXTI_isset(EXTI5)){
		if(state == ATT){
			state = PRE;
		}
		EXTI_clear(EXTI5);
	}
}


void EXTI4_IRQHandler(void){  //pulsante di disattivazione allarme
	if(EXTI_isset(EXTI4)){
		if(state == ATT){
			state = ATT_OK;
		}
		EXTI_clear(EXTI4);
	}
}


void TIM2_IRQHandler(void){

	if(TIM_update_check(TIM2)){

		show_state();
		switch(state){

			case PRE_ATT:{

				GPIO_toggle(GPIOC, 3);
				timing.tick_counter++;

				if(timing.tick_counter >= timing.exit_time){
					state = ATT;
					GPIO_write(GPIOB, 0, 1);
					GPIO_write(GPIOC, 3, 0);
					timing.tick_counter = 0;
				}

				break;
			}

			case PRE:{

				GPIO_write(GPIOB, 0, 0);
				GPIO_write(GPIOC, 2, 1);

				timing.tick_counter++;

				if(timing.tick_counter >= timing.enter_time){
					state = ALL;
					GPIO_write(GPIOC, 2, 0);
					timing.tick_counter = 0;
				}
				break;
			}

			case ALL:{
				GPIO_toggle(GPIOB, 0);
				break;
			}

			}

		TIM_update_clear(TIM2);
	}
}


int main(int argc, char *argv[]){

	timing.tick_counter = 0;
	timing.exit_time = 25;
	timing.enter_time = 100;

	config();

	for(;;){

		switch(state){

		case DIS:{

			GPIO_write(GPIOC, 3, 1);
			GPIO_write(GPIOB, 0, 0);
			GPIO_write(GPIOC, 2, 0);
			DISPLAY_puts(0, "DIS ");

			timing.tick_counter = 0;

			if(kbhit()){
				char c = readchar();
				if(c == '!'){
					state = SETP;
					GPIO_write(GPIOC, 3, 0);
					printf("***SETUP***\n");
				}
			}

			break;
		}

		case PRE_ATT_OK:{
			if(ask_pwd())
				state = PRE_ATT;
			else
				state = DIS;
			break;
		}

		case ATT_OK:{
			check_pwd();
			break;
		}

		case PRE:{
			check_pwd();
			break;
		}

		case ALL:{

			GPIO_write(GPIOC, 2, 0);
			while(!ask_pwd()){
				state = ALL;
			}

			state = DIS;
			GPIO_write(GPIOB, 0, 0);
			break;
		}

		case SETP:{

			char s[DIM];
			settings(s);
			break;
		}

		}
	}

	return 0;
}

/*
 * gestione tempistiche
 * 200 ms ---> tempo lampeggio led
 * 5s --> 5000ms --> 25 periodi
 * 20s --> 20000ms --> 100 periodi
 *
 *TIM_config_timebase(TIM2, 8400, 2000);
*/

/*
 *  PASSWORD <xyz>
 *  OUT-TIME <valore>
 *  IN-TIME <valore>
 *  EXIT
 *
 *  usare la strtok per tokenizzare la stringa passata
 *  poi confrontare la prima stringa con PASSWORD, con
 *  IN-TIME e con OUT-TIME e in base ai vari casi usare
 *  atoi per convertire la seconda stringa tokenizzata
 *  in valore intero.
 *
 *  mi serve la strtok e la atoi
 *
*/
