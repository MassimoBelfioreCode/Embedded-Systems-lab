/*
 * distributore_automatico.c
 *
 *  Created on: 19 feb 2024
 *      Author: massimo
 */

#include <stm32_unict_lib.h>
#include <stdio.h>
#include <string.h>

#define DIM 5

enum drink{
	AL, AG, br
};

enum drink drinks[3] = {AL, AG, br};
char str[DIM];

enum{
	IDLE, SETUP, EROG, STOP_EROG
};


int state = IDLE;
int selected_drink = -1;

volatile float level = 0;
volatile float C = 0;
volatile float glass = 0;

volatile int count = 0;


void config(){

	DISPLAY_init();
	CONSOLE_init();

	GPIO_init(GPIOB);
	GPIO_init(GPIOC);

	GPIO_config_output(GPIOB, 0);   //LED ROSSO
	GPIO_config_output(GPIOC, 2);   //LED GIALLO
	GPIO_config_output(GPIOC, 3);   //LED Verde
	GPIO_config_output(GPIOB, 8);   //due punti display

	GPIO_config_input(GPIOB, 10);	//pulsante X
	GPIO_config_input(GPIOB, 4);	//pulsante Y
	GPIO_config_input(GPIOB, 5);    //pulsante Z
	GPIO_config_input(GPIOB, 6);    //pulsante T

	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	GPIO_config_EXTI(GPIOB, EXTI4);
   	EXTI_enable(EXTI4, FALLING_EDGE);

	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

	GPIO_config_EXTI(GPIOB, EXTI6);
	EXTI_enable(EXTI6, FALLING_EDGE);

	//TIMER 2
	TIM_init(TIM2); //5ms
	TIM_config_timebase(TIM2, 41999, 999); //SIMBOLO OGNI 0.5 SEC FLASH

	TIM_set(TIM2, 0);
	TIM_on(TIM2);

	TIM_enable_irq(TIM2, IRQ_UPDATE);

	ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_on(ADC1);

}


void TIM2_IRQHandler(){

	if(TIM_update_check(TIM2)){

		switch(state){

		case EROG:{

			count++;
			level += 5.0;

			/*
			if(count == 2){
				level += 10.0;
				count = 0;
			}
			*/
			break;
		}

		}
		TIM_update_clear(TIM2);
	}
}

//Tasto X
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		if(state == IDLE){
			state = EROG;
			selected_drink = 0;
		}
		EXTI_clear(EXTI10);
	}
}

//Tasto Y
void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		if(state == IDLE){
			state = EROG;
			selected_drink = 1;
		}
		EXTI_clear(EXTI4);
	}
}

//Z e T
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) {
		if(state == IDLE){
			state = EROG;
			selected_drink = 2;
		}
		EXTI_clear(EXTI5);
	}

	if (EXTI_isset(EXTI6)) {
		if(state == IDLE)
			state = SETUP;
		else if(state == SETUP)
			state = IDLE;
		EXTI_clear(EXTI6);
	}
}

/*
 *
 *  CONSIDERAZIONI TEMPISTICHE
 *
 *	AN11 [30, 100] con risoluzione di 5ml/s
 *
 *30   0
 *35   1
 *40   2
 *45   3
 *50   4
 *55   5
 *60   6
 *65   7
 *70   8
 *75   9
 *80   10
 *85   11
 *90   12
 *95   13
 *100  14
 *
 *
 *10 ml/s rubinetto quindi eroga 10ml ogni secondo
 *
 *il valore di C lo devo impostare girando la manopola
 *
 *scritta display lampeggia ogni 0.5 s
 *
 *
 *	0.5s
 *	5ml ogni 0.5s rubinetto
 *
 *	Possibili configurazioni:
 *
 *	vedere esercitazione 2
 *
 */


void print(){
	switch(selected_drink){

		case AL:{
			DISPLAY_puts(0, "AL  ");
			printf("Erogazione Acqua-Liscia\n");
			break;
		}

		case AG:{
			DISPLAY_puts(0, "AG  ");
			printf("Erogazione Acqua-Gasata\n");
			break;
		}

		case br:{
			DISPLAY_puts(0, "br  ");
			printf("Erogazione Birra\n");
			break;
		}
	}
}




void menu(char *str){

	//MANOPOLA AN11
	ADC_sample_channel(ADC1, 11);
	ADC_start(ADC1);
	while(!ADC_completed(ADC1)){}
	int adcval = ADC_read(ADC1) * 14.0 / 63;
	//C = adcval *(100 - 30) / 63.0 + 30;
	C = adcval * 5 + 30;

	sprintf(str, "%4d", (int)C);
	DISPLAY_puts(0, str);
}


int main(int argc, char **argv){

    ClockConfig();
	config();

	printf("SELEZIONARE UNA BIBITA DAL MENU \n");
	printf("PREMERE TASTO X PER SELEZIONARE ACQUA-LISCIA\n");
	printf("PREMERE TASTO Y PER SELEZIONARE ACQUA-GASATA\n");
	printf("PREMERE TASTO Z PER SELEZIONARE BIRRA\n");
	printf("PREMERE TASTO T PER APRIRE IL MENU \nE IMPOSTARE C\n");
	char s[DIM];

	for(;;){

		switch(state){

		case IDLE:{

			DISPLAY_puts(0, "Idle");

			GPIO_write(GPIOB, 0, 0);
			GPIO_write(GPIOC, 2, 0);
			GPIO_write(GPIOC, 3, 0);

			break;
		}

		case EROG:{

			switch(selected_drink){

				case AL:{

					GPIO_write(GPIOB, 0, 1);

					break;
				}

				case AG:{

					GPIO_write(GPIOC, 2, 1);

					break;
				}

				case br:{

					GPIO_write(GPIOC, 3, 1);

					break;
				}

			}

			while(level < C){

				if(level <= C/2){
					if(count % 2 == 0)
						print();
					else
						DISPLAY_puts(0, "    ");
				}
				else if(level > C/2){
					GPIO_write(GPIOB, 8, 1);

					if(count % 2 == 0){
						sprintf(str, "%4d", (int)level);
						DISPLAY_puts(0, str);
					}
				}
			}

			state = STOP_EROG;

			break;
		}

		case STOP_EROG:{

			printf("Fine erogazione\n");

			switch(selected_drink){

				case AL:{

					GPIO_write(GPIOB, 0, 0);

					break;
				}

				case AG:{

					GPIO_write(GPIOC, 2, 0);

					break;
				}

				case br:{

					GPIO_write(GPIOC, 3, 0);

					break;
				}

			}

			count = 0;
			level = 0;
			GPIO_write(GPIOB, 8, 0);
			state = IDLE;

			break;
		}

		case SETUP:{

			menu(s);

			break;
		}

		}
	}

	return 0;
}
