#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int pipes[2];
	int infile;
	int outfile;
	char buff[2054];

	pipe(pipes);

	// outfile = open("./outfile1.txt",  O_WRONLY | O_TRUNC);

	// // close(pipes[0]);
	// // close(pipes[1]);
	// // close(outfile);
	// write(outfile, "test\n", 5);

	// close(outfile);

	// memset(&buff, 0, 2054);
	// infile = open("./outfile1.txt", O_RDONLY);
	
	// read(infile, buff, 1);

	// printf("%s\n", buff);

	write(pipes[1], "test\n", 5);


	read(pipes[0], buff, 2054);

	printf("%s\n", buff);
}