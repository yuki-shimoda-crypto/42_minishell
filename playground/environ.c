#include <stdio.h>

int main(void)
{
	extern char **environ;

	for (int i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}

