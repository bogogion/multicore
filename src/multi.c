#include "multi.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t setup_control_struct(mc_ctrl_struct *control, size_t num_processors, void *data, size_t data_size){
	control->num_processors = num_processors;
	control->data_size = data_size;
	if(data_size > 0)
	{
		memcpy(control->data,data,data_size);
	}
}

uint8_t setup_shm(const char *shm_name, mc_ctrl_struct control_struct)
{
	size_t control_size = (sizeof(control_struct) + control_struct.data_size);

	int sfd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRWXU);
	if(sfd < 0)
	{ return 0; }

	if (ftruncate(sfd,control_size) < 0)
	{ return 0; }

	char *data = mmap(NULL, control_size, PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);
	if(data != NULL)
	{
		memcpy(data,&control_struct,control_size);
	} else {
		return 0;
	}

	munmap(data,control_size);
	return 1;
}

size_t get_size_of_control(mc_ctrl_struct control_struct)
{
	return(sizeof(control_struct) + control_struct.data_size);
}

uint8_t spawn_processors(uint16_t num_processors, const char *shm_name, size_t shm_size)
{
	char buf[256];
	for(uint16_t i = 0; i < num_processors; i++)
	{
		sprintf(buf,PROCESSOR_EXEC_PATH" %i %s %i &", i, shm_name, shm_size);
		system(buf);
	}
	return 1;
}
