#ifndef multicore_config_h
#define multicore_config_h

#define PROCESSOR_EXEC_PATH "./processor"

#define HARDCORE
//#define SOFTCORE

#define AUTO_DETERMINE_CORES

#ifdef AUTO_DETERMINE_CORES
#define MAX_AMOUNT_OF_CORES 128
#endif

#ifndef AUTO_DETERMINE_CORES
#define CORE_COUNT 4
#endif

#endif
