#include "src/multi.h"
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

int run = 1;

void intHandler(int useless)
{
	run = 0;
}

int main(int argc, char *argv[])
{
	//	printf("%i cores\n",find_num_cores());
	mc_ctrl_struct control;
	setup_control_struct(&control, find_num_cores(), NULL, 0);
	//setup_control_struct(&control, 4, NULL, 0);

	setup_shm("test",control);

	spawn_processors(find_num_cores(),"test",get_size_of_control(control));
	//spawn_processors(4,"test",get_size_of_control(control));

	signal(SIGINT, intHandler);
	signal(SIGTERM, intHandler);

	while(run){}



	for(int i = 0; i < control.num_processors; i++)
	{
		kill(control.pids[i], SIGTERM);
	}

	shm_unlink("test");
	return 1;
}
