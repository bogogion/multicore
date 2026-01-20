#ifndef multicore_multi_h
#define multicore_multi_h

#include "config.h"
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

/* add your own control codes here.. or not idc */
#define MULTICORE_PROCESSOR_ONLINE 1


typedef struct control_struct
{
	size_t num_processors;
	size_t processors_in_use;
	
	#ifdef AUTO_DETERMINE_CORES
	uint8_t processor_control[MAX_AMOUNT_OF_CORES];
	pid_t   pids[MAX_AMOUNT_OF_CORES];
	#else
	uint8_t processor_control[CORE_COUNT];
	pid_t   pids[CORE_COUNT];
	#endif

	void *data;
	size_t data_size;
} mc_ctrl_struct;

int8_t setup_control_struct(mc_ctrl_struct *control, size_t num_processors, void *data, size_t data_size);
int8_t setup_shm(const char *shm_name, mc_ctrl_struct control_struct);
int8_t spawn_processors(uint16_t num_processors, const char *shm_name, size_t shm_size);

static inline size_t get_size_of_control(mc_ctrl_struct control_struct)
{
	return(sizeof(control_struct) + control_struct.data_size);
}

#ifdef AUTO_DETERMINE_CORES
static inline uint16_t find_num_cores()
{
	return((uint16_t)sysconf(_SC_NPROCESSORS_ONLN));
}
#endif

#endif
