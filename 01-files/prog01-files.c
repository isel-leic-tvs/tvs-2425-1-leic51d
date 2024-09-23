#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// Every process has its own file descriptor table (in kernel space).
// File descriptors are positive integer values, that are indices to this table.
// Entries 0, 1, 2 refer to standard input, standard output, and standard error, respectively.
// Opening a file occupies another entry.

// COMPILE:
//   gcc -o prog01 prog01-files.c
//
// RUN:
//   ./prog01 output.txt

int main(int argc, const char * argv[]) {
	puts("prog01 running");

	if (argc != 2) {
		fprintf(stderr, "Args: output_file_name\n");
		exit(1);
	}

	// fd will likely be 3, the first available entry
	int fd = open(argv[1], O_CREAT | O_RDWR, 0644);
	if (fd == -1) {
		perror("Failed to open file.");
		fprintf(stderr, "Failed to open \"%s\"\n", argv[1]);
		exit(2);
	}
	printf("fd = %d\n", fd);

	// Write into the I/O session associated with
	// entry 'fd' (3?) of the file descriptor table
	write(fd, "Hello, world!\n", 14);
	// TO DO : check errors

	// Write into the I/O session associated with the
	// standard output (file descriptor table entry 1)
	write(1, "DONE\n", 5);

	close(fd);

	return 0;
}
