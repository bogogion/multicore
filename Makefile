all:
	gcc config.h main.c multi.* sys_info.* -o main && gcc config.h multi.* processor.c -o processor
