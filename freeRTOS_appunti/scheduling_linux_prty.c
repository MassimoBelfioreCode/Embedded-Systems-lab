#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

/*
struct sched_param {
	int sched_priority;
};
*/

#define RR

int child_process(int id){

	struct sched_param params;
	int i, k;

/*imposta i parametri di schedulazione sulla base della
  #define di una costante simbolica*/
#ifdef FIFO
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	if(sched_setscheduler(0, SCHED_FIFO, &params) < 0){
		perror("Cannot set the scheduler");
	}
	printf("Setting priority %d\n", params.sched_priority);
#endif

#ifdef RR
	params.sched_priority = sched_get_priority_max(SCHED_RR) - id;
	if(sched_setscheduler(0, SCHED_RR, &params) < 0){
		perror("Cannot set the scheduler");
	}
	printf("Setting priority %d\n", params.sched_priority);
#endif

	usleep(500000);
	printf("child %d started\n", id);
	//codice corpo del processo figlio, serve per provare lo sched_fifo
	for(int i = 0; i < 5; i++){
		printf("child %d iteration %d\n", id, i);
		for(k = 0; k < 100000000; k++){}
	}
	//nel for ultimo faccio in quel modo per tenere occupata la CPU
	return 0;
}


int main(int argc, char **argv){

	int i, status;
	printf("Starting 3 children...\n");
	
	/*RETURN VALUE
        On success, the PID of the child process is returned in the parent, and
        0  is returned in the child.  On failure, -1 is returned in the parent,
        no child process is created*/
	
	for (i = 0; i < 3; i++){
		pid_t pid = fork();
		if(pid == 0){
			child_process(i);
			exit(0);
		}
	}

	//qui il processo padre chiama la sys call wait in attesa
	//che tutti i processi figli terminino, e dopo termina lui
	printf("Waiting...\n");
	while(wait(&status) > 0){};
	printf("End...\n");
}

