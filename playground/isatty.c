/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:13:51 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/13 14:31:24 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

// int main(int argc, char const *argv[])
// {
// 	char	*str;

// 	if (argc > 1)
// 		str = argv[1];
// 	else if (isatty(STDIN_FILENO))
// 	{
// 		fget
// 	}

// int	fd;
// 	if (isatty(STDIN_FILENO))
// 		printf("%s\n", "connect stdin to terminal");
// 	else
// 		printf("%s\n", "NG");
// 	close(STDIN_FILENO);
// 	if (isatty(STDIN_FILENO))
// 		printf("%s\n", "connect stdin to terminal");
// 	else
// 		printf("%s\n", "NG");
// 	fd = open("/dev/stdin", O_RDONLY);
// 	printf("%d\n", fd);
// 	if (isatty(fd))
// 		printf("%s\n", "connect stdin to terminal");
// 	else
// 		printf("%s\n", "NG");
// 	return (0);
// }

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }
    } else if (isatty(STDIN_FILENO)) {
        printf("Enter input: ");
        fp = stdin;
    } else {
        fp = fopen("/dev/stdin", "r");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }
    }

    while ((c = getc(fp)) != EOF) {
        putchar(c);
    }

    fclose(fp);
    return 0;
}