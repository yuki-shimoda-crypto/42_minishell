#include <stdio.h>
#include <stdlib.h>

//int	function(void) __attribute__((noreturn));

//int	function(void)
//{
//	printf("function\n");
//}

void	func_void(void) __attribute__((noreturn));

void	func_void(void)
{
	printf("void	func_void(void)\n");
	exit(0);
}

int main(void)
{
	//function();
	func_void();
	return (0);
}

//void	fatal_error(const char *msg) __attribute__((noreturn));
//
//void	fatal_error(const char *msg)
//{
//	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
//	exit(1);
//}
//
//int	interpret(char *line)
//{
//	extern char	**environ;
//	char		*argv[] = {line, NULL};
//	pid_t		pid;
//	int			wstatus;
//
//	pid = fork();
//	if (pid < 0)
//		fatal_error("fork");
//	else if (pid == 0)
//	{
//		// child process
//		execve(line, argv, environ);
//		fatal_error("execve");
//	}
//	else
//	{
//		// parent process
//		wait(&wstatus);
//		return (WEXITSTATUS(wstatus));
//	}
//}
