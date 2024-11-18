// Requests that a file is loaded into the process address space
// fptr will to the file contents in memory

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "use: %s filename\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("Failed to open file");
		exit(2);
	}
	
	printf(":: RUNNING %d ::\n", getpid());

	long fsize = lseek(fd, 0, SEEK_END);
	printf("File size: %ld\n", fsize);

	getchar();

	void * fptr = mmap(NULL, fsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	close(fd);
	
	puts((char *)fptr);

	getchar();
	
	memcpy(fptr, "XXXX - XXXX - XXX", 17);

	puts((char *)fptr);

	getchar();

	munmap(fptr, fsize);
	return 0;
}
