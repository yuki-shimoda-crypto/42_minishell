#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char	*str = strndup("test", 0);
	printf("%s\n", str);
	free(str);
	return (0);
}
