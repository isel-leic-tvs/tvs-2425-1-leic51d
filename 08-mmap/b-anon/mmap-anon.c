// Requests that a file is loaded into the process address space
// fptr will to the file contents in memory

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define SIZE 4*1024*1024

int main() {
	printf(":: RUNNING %d ::\n", getpid());
	getchar();

	// Direct memory allocation, always in multiples of PAGE_SIZE 
	void * fptr = mmap(NULL, SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	getchar();
	
	munmap(fptr, SIZE);
	return 0;
}
