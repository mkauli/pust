# pust
Linux driver to establish event trigger between TI-PRU and host cpu user-space application. The TI-PRU is a Programmable Real-Time Unit Subsystem on many TI CPUs (for example AM335x cpu family) controlled by the remoteproc driver of Linux.

This driver creates files in the sys-fs filesystem - Linux user space applications can use pull to wait for trigger events of the PRU unit. 
