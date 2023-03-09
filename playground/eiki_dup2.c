#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

int	main(void)
{
	int	fd;
	int	fd2;
	int	fd_dup;
	int	stdout;

	stdout = STDOUT_FILENO;

	fd = open("eiki.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_dup = fcntl(stdout, F_DUPFD, 10);
	// fd2 = fcntl(fd, F_DUPFD, 10);
	// fd2 = dup2(fd + 10, fd);
	// fd_dup = dup2(stdout + 10, stdout);
	// close(stdout);
	dup2(fd, stdout);
	close(fd);
	printf("redirect");
/////////////////////////////////////
	// dup2(fd_dup, fd2);
	dup2(STDOUT_FILENO, fd_dup);
	close(fd_dup);
	printf("reset");
	return (0);
}