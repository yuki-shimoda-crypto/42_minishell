#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

int main(void)
{
	if (close(INT_MAX) == -1)
	{
		printf("%s\n", "error");
		exit(1);
	}
	printf("%s\n", "OK");
	
	return (0);
}
