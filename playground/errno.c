/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:54:49 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/11 12:54:49 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, const char *argv[])
{
	fprintf(stderr, "Eacces: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	errno = EIO;
	perror(argv[0]);
	exit(0);
}



























