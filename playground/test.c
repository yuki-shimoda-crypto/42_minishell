#include <stdio.h>

int main(void)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};

	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	return (0);
}
