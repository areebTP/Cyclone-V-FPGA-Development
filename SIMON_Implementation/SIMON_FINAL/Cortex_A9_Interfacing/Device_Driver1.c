/* Device_Driver1.c
 * Author: STUDENT ID B820928
 This source file contains the necessary functions for accessing virtual memory 
 in linux to communication with the FPGA. Corresponding file for Device_Driver1.h 
 */

#include "Device_Driver1.h" // include the driver header file 

//---------------------------------------------------LINUX KERNAL FUNCTIONS

/* Open /dev/mem to give access to physical addresses */
int open_physical(int fd)
{
	if (fd == -1) // check if already open
		if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
		{
			printf("ERROR: could not open \"/dev/mem\"...\n");
			return (-1);
		}
	return fd;
}

/* Close /dev/mem to give access to physical addresses */
void close_physical(int fd)
{
	close(fd);
}

/* Establish a virtual address mapping for the physical addresses starting
 * at base and extending by span bytes */
void* map_physical(int fd, unsigned int base, unsigned int span)
{
	void* virtual_base;
	// Get a mapping from physical addresses to virtual addresses
	virtual_base = mmap(NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED,
		fd, base);
	if (virtual_base == MAP_FAILED)
	{
		printf("ERROR: mmap() failed...\n");
		close(fd);
		return (NULL);
	}
	return virtual_base;
}

/* Close the previously-opened virtual address mapping */
int unmap_physical(void* virtual_base, unsigned int span)
{
	if (munmap(virtual_base, span) != 0)
	{
		printf("ERROR: munmap() failed...\n");
		return (-1);
	}
	return 0;
}