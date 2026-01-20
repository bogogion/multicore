# multicore
multicore is a simple mini-library for running functions across multi cpu cores. 

developed solely by zane.

![](https://img.shields.io/badge/version-0.2-blue)

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
