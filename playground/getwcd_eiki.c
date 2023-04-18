#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
// #define PATH_MAX 256

int	main(void)
{
	char	*str;
	size_t	size;

	size = PATH_MAX;
	while (1)
	{
		str = malloc(sizeof(char) * size);
		if (!str)
		{
			perror("NULL");
			return (1);
		}
		if (getcwd(str, size) != NULL)
			break ;
		if (errno != ERANGE)
		{
			perror("NULL");
			return (1);
		}
		size *= 2;
		free(str);
	}
	free(str);
	return (0);
}
