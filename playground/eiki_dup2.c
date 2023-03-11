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
	// fd_dup = fcntl(STDOUT_FILENO, F_DUPFD, 10);
	fd_dup = dup2((STDOUT_FILENO + 10), STDOUT_FILENO);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	write(1, "redirect\n", 9);
	// printf("test1\n");
/////////////////////////////////////
	dup2(fd_dup, STDOUT_FILENO);
	close(fd_dup);
	write(1, "reset\n", 5);
	// printf("test2\n");
	return (0);
}