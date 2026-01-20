#include "sys_info.h"
#include <unistd.h>

#ifdef AUTO_DETERMINE_CORES

uint16_t find_num_cores()
{
	return((uint16_t)sysconf(_SC_NPROCESSORS_ONLN));
}

#endif


