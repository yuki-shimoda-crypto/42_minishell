#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char	*str;

	str = NULL;
	if (!access("/bin/bash", F_OK))
		printf("%s\n", "OK");
	else
		printf("%s\n", "NG");
	return (0);
}
