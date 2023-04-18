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
// #include <limits.h>
// 
// int main(void)
// {
// //	int		fd;
// 	int		old_fd;
// 	int		save;
// 
// //	fd = open("yshimoda.txt",  O_RDWR | O_CREAT | O_TRUNC, 0644);
// //	if (fd < 0)
// //		return (dprintf(STDERR_FILENO, "error\n"));
// 	old_fd = STDOUT_FILENO;
// 	save = dup2(old_fd, 1048575);
// 	if (save == -1)
// 	{
// 		printf("%s\n", "error");
// 		exit(1);
// 	}
// 	close(old_fd);
// 	write(STDOUT_FILENO, "dupped\n", strlen("dupped\n"));
// 	dup2(save, STDOUT_FILENO);
// 	close(save);
// 	write(STDOUT_FILENO, "end\n", strlen("end\n"));
// 	return (0);
// }
// 

#include <stdio.h>

int main(void)
{
	int		save;
	int		fd;

	write(STDOUT_FILENO, "test1\n", strlen("test1\n"));
	save = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	write(STDOUT_FILENO, "test2\n", strlen("test2\n"));
	dup2(save, STDOUT_FILENO);
	close(STDOUT_FILENO);
	close(STDOUT_FILENO);
	return (0);
}