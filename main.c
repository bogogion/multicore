#include "sys_info.h"
#include "multi.h"
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	printf("%i cores\n",find_num_cores());
	mc_ctrl_struct control;
	setup_control_struct(&control, find_num_cores(), NULL, 0);
	setup_shm("test",control);

	spawn_processors(find_num_cores(),"test",get_size_of_control(control));

	while(1){}
	shm_unlink("test");
	return 1;
}
