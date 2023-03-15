/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:38:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/15 21:06:47 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

// int	wrap_close(int fd)
// {
// 	int	result;
// 
// 	result = close(fd);
// 	if (result == -1)
// 	{
// 		perror(NULL);
// 		assert_error("close\n");
// 	}
// 	return (result);
// }

int wrap_close(int fd)
{
    int ret;

    ret = close(fd);
    if (ret == -1)
    {
        perror("close");
        g_return_error.exec_error = true;
    }
    return (ret);
}
