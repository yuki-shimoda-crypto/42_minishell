#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int		old_fd;
	int		save;

//	fd = open("tmp.txt",  O_RDWR | O_CREAT | O_TRUNC, 0644);
//	if (fd < 0)
//		return (dprintf(STDERR_FILENO, "error\n"));
	old_fd = 1;
	save = dup2(10, old_fd);
	close(old_fd);
	dup2(1, save);
	close(save);
	printf("%s\n", "dup");
	write(1, "write\n", strlen("write\n"));
//	dup2(1, fd);
//	close(fd);
//	printf("dupped\n");
//	dup2(1, save);
//	close(save);
//	printf("end\n");
	return (0);
}
