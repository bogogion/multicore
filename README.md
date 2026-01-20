# multicore
multicore is a simple mini-library for running functions across multi cpu cores. 

developed solely by zane in about a day

![](https://img.shields.io/badge/version-1.0-blue)

## features
- Sharing of data and controlling individual processes via shm on linux.
- Designed for UNIX systems with little overhead.
- Run whatever code you want.
- Ability to lock execution to specific cores to allow for better parallel processing.
- Allows for *n* amount of cores to be used.

## limitations
- For GNU/Linux only. FreeBSD support is possible by switching around some system calls, primarily those for running commands and getting/setting CPU information.
- Requires a standalone binary to be built and run.
- Requires use of shm which can be readable/insecure (by default only by the same user who starts the program).

# how to use
the only dependencies in this project is the standard C library and GNU utils. gcc is also the default compiler but there is no specific need for it.

instructions are as followed:
1. in `processor.c` in the `mainloop` function place any sort of logic code for the processor. this can be another function referenced from a different file or you can edit this part inside the `processor.c` file
2. run `make` to compile the processor into it's ready to use binary.
3. in `src/config.h` setup the relative path (or absolute path) to the processor binary. by the default, this path is simply `./processor` if you run it in this repo. if you move it around, or this repo is nested deeper into a project, you will need to change this. this path works off of *where you run your main program* and is not relative to `src/multi.c` or `src/config.h`

## configuration
in `src/config.h` there are macros that define some of the program's functionality.

- `AUTO_DETERMINE_CORES` - when defined will use ALL cores on the system automatically
- `MAX_AMOUNT_OF_CORES`  - determines the max amount of cores available (this also mean virtual cores) and is default set to 128. if for some reason you are on a computer with more than 128 cores, or have some weird core schema setup, change this accordingly
- `CORE_COUNT` - only enabled if auto determine is off. this is just the amount of cores to be used. the library automatically launches processes starting from the 0 core, however this can be changed in `src/multi.c`
- `HARDCORE` - enables pinning of execution to specific cores. 
- `PROCESSOR_EXEC_PATH` - path relative to your main application where `processor` is located.

## example code
this is an example that also sets up the shared memory space and launches the processors.
```c
#include "src/multi.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>

int run = 1

void intHandler(int useless)
{
	run = 0;
}

int main(int argc, char *argv[])
{
	/* Create our control struct */
	mc_ctrl_struct  control;
	
	/* Here is where you'd put any external data the processors need to be able to view */
	void *data = NULL;
	size_t data_size = 0;
	
	/* Init our control struct and shm */
	setup_control_struct(&control, find_num_cores(), data, data_size);
	if(setup_shm("test",control) < 0)
	{ return -1; }
	
	/* Start our processors */
	if(spawn_processors(find_num_cores(),"test",get_size_of_control(control)) < 0)
	{ return -1; }
	
	signal(SIGINT, intHandler);
	/* Wait for SIGINT from host, this can be any other logic as well */
	
	while(run){}
	
	/* Close out our processes once we are doing running */
	for(int i = 0; i < control.num_processors; i++)
	{
		kill(control.pids[i],SIGTERM);
	}
	
	shm_unlink("test");
	return 1;
}

```
