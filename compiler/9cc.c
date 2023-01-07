#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "error\n");
		return (1);
	}
	printf("%s\n", ".intel_syntax noprefix");
	printf("%s\n", ".globl main");
	printf("%s\n", "main:");
	printf("	mov rax , %d\n", atoi(argv[1]));
	printf("%s\n", "	ret");
}
