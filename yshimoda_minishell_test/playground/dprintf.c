#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main(int argc, const char *argv[])
{
	int	fd;

	if (argc == 1)
		fd = STDOUT_FILENO;
	else
		fd = open(argv[1], O_RDWR|O_CREAT, LOCKMODE);
	dprintf(fd, "dprintf\t%d%s\n", 644, "test");
	return (0);
}

