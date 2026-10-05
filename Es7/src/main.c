/*
 * main.c
 *
 *  Created on: 13 dic 2023
 *      Author: massimo
 */

//implementare la tastiera

//funzione per dire il tasto premuto

#include <stm32_unict_lib.h>
#define N 4

//matrice 4 x 4
char key_matrix[][N] = {
						 {'1','2','3','A'},
						 {'4','5','6','B'},
						 {'7','8','9','C'},
						 {'*','0','#','D'}
                       };


void setup(){

	CONSOLE_init();

	GPIO_init(GPIOA);
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);

	GPIO_PULL_UP(GPIOB, 10);
	GPIO_config_input(GPIOC, 7);

	GPIO_PULL_UP(GPIOA, 8);
	GPIO_config_input(GPIOA, 8);

	GPIO_PULL_UP(GPIOA, 9);
	GPIO_config_input(GPIOA, 9);

	GPIO_PULL_UP(GPIOC, 7);
	GPIO_config_input(GPIOC, 7);

	//output
	GPIO_config_output(GPIOB, 3);
	GPIO_config_output(GPIOB, 4);
	GPIO_config_output(GPIOB, 5);
	GPIO_config_output(GPIOA, 10);

	TIM_init(TIM2);

	//TIM_config_timebase(TIM2, )

	TIM_set(TIM2, 0);
	TIM_on(TIM2);

	TIM_enable_irq(TIM2, IRQ_UPDATE);
}


void TIM2_IRQHandler(void){

}


int read_row(){

	if(GPIO_read(GPIOC, 7) == 0)
		return 0;
	else if(GPIO_read(GPIOA, 9) == 0)
		return 1;
	else if(GPIO_read(GPIOA, 8) == 0)
		return 2;
	else if(GPIO_read(GPIOB, 10) == 0)
		return 3;

	return -1;
}


void setColumn(){


}


void loop(){


	//i e j sono indici di riga e colonna

	for(register int i = 0; i < N; i++){
		for(register int j = 0; j < N; j++){


		}
	}

}



int main(int argc, char **argv){

	setup();

	for(;;){

		loop();
	}

	return 0;
}
