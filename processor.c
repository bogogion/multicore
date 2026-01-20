#define _GNU_SOURCE
#include "src/config.h"
#include "src/multi.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>


int run = 1;

void sigHandler(int useless){ run = 0; }

void mainloop(mc_ctrl_struct *control, int core_id)
{
	/* do what u want here */
	printf("[core %i] Hello world!\n",core_id);
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("[multicore] Processor not given enough arguments.\n");
		return 1;
	}
	
	int core_id = atoi(argv[1]);
	
	/* fuck it we ball */
	int sfd = shm_open(argv[2], O_RDWR, 0);

	if(sfd < 0)
	{ 
		printf("[multicore] Issue with shm...\n");
		perror("shm");
		return 1;
	}


	mc_ctrl_struct *control = (mc_ctrl_struct*)mmap(NULL,(size_t)atoi(argv[3]), PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0 );

	if(control == NULL)
	{
		printf("[multicore] mmap failure...\n");
		return 1;
	}

	/* setup core specific stuff */
	
	control->processor_control[core_id] = (uint8_t)MULTICORE_PROCESSOR_ONLINE;
	control->pids[core_id] = getpid();

	#ifdef HARDCORE
	/* for hardcore mode we restrict each process to an individual core */
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(core_id, &set);
	sched_setaffinity(0, sizeof(cpu_set_t), &set);
	#endif

	while(run)
	{
		mainloop(control,core_id);
	}

	munmap(control,(size_t)atoi(argv[3]));

	//shm_unlink(argv[2]);
	return 0;
}

