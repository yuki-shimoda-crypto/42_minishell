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
	int	stdout_1;

	stdout_1 = 0;
	fd = open("eiki.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// fd_dup = fcntl(STDOUT_FILENO, F_DUPFD, 10);
	stdout_1 = dup2(STDOUT_FILENO, stdout_1);
	// close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	write(1, "redirect\n", 9);
	// printf("test1\n");
/////////////////////////////////////
	dup2(stdout_1, STDOUT_FILENO);
	close(stdout_1);
	write(1, "reset\n", 5);
	// printf("test2\n");
	return (0);
}