#ifndef multicore_sys_info_h
#define multicore_sys_info_h

#include <stdint.h>
#include "config.h"

#ifdef AUTO_DETERMINE_CORES
uint16_t find_num_cores();
#endif

#endif
