#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int		status;
	int		fd_1;
	int		fd_2;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	fd_1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_1 < 0)
	{
		printf("open error\n");
		exit(1);
	}
	dup2(fd_1, 1);
	fd_2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_2 < 0)
	{
		printf("open error\n");
		exit(1);
	}
	dup2(fd_2, fd_1);
	while(1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		free(line);
		printf("test\n");
	}
	exit(status);
}

