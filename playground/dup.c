#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

//int main(int argc, const char *argv[])
//{
//	int		status;
//	int		fd_1;
//	int		fd_2;
//	char	*line;
//
//	rl_outstream = stderr;
//	status = 0;
//	fd_1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
//	if (fd_1 < 0)
//	{
//		printf("open error\n");
//		exit(1);
//	}
//	dup2(fd_1, 1);
//	fd_2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
//	if (fd_2 < 0)
//	{
//		printf("open error\n");
//		exit(1);
//	}
//	dup2(fd_2, fd_1);
//	while(1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		if (*line)
//			add_history(line);
//		free(line);
//		printf("test\n");
//	}
//	exit(status);
//}

#include <stdio.h>

//int	stashfd(int fd)
//{
//	int	stashfd;
//
//	stashfd = fcntl(fd, F_DUPFD, 10);
//	if (stashfd < 0)
//		fatal_error("fcntl");
//	if (close(fd) < 0)
//		fatal_error("close");
//	return (stashfd);
//}

int main(void)
{
	int		fd;
	int		old_fd;
	int		save;

	fd = open("yshimoda.txt",  O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (dprintf(STDERR_FILENO, "error\n"));
	old_fd = STDOUT_FILENO;
	save = dup2(old_fd + 10, old_fd);
	close(old_fd);
	dup2(STDOUT_FILENO, fd);
	close(fd);
	printf("dupped\n");
	dup2(STDOUT_FILENO, save);
	close(save);
	printf("end\n");
	return (0);
}
