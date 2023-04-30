#include <sys/stat.h>
#include <stdio.h>

int	main(int argc, const char *argv[])
{
	struct stat st;

	if (argc < 2)
		return (1);
	if (stat(argv[1], &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			printf("argv is file\n");
		else if (S_ISDIR(st.st_mode))
			printf("argv is directory\n");
		else
			printf("argv is not a file or directory\n");
	}
	else
	{
		perror(NULL);
		printf("error\n");
	}
	return (0);
}

