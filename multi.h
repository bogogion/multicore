#ifndef multicore_multi_h
#define multicore_multi_h

#include "config.h"
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#define MULTICORE_PROCESSOR_ONLINE 1


typedef struct control_struct
{
	size_t num_processors;
	size_t processors_in_use;
	
	uint8_t *processor_control;

	pid_t *pids;

	void *data;
	size_t data_size;
} mc_ctrl_struct;

uint8_t setup_control_struct(mc_ctrl_struct *control, size_t num_processors, void *data, size_t data_size);
uint8_t setup_shm(const char *shm_name, mc_ctrl_struct control_struct);
size_t  get_size_of_control(mc_ctrl_struct control_struct);
uint8_t spawn_processors(uint16_t num_processors, const char *shm_name, size_t shm_size);
void cleanup(mc_ctrl_struct *control); /* cleans up memory and closes out processors */

#endif
