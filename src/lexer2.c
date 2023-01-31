/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:08:17 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/13 20:33:04 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static	int	check_quoted(t_lexer_utils	*split_box, int i)
// {
// 	int	j;
// 	int	flag;

// 	j = 0;
// 	flag = 0;
// 	while (split_box->tmp[i][j])
// 	{
// 		if (split_box->tmp[i][0] == '"' || split_box->tmp[i][0] == '\'')
// 			flag = 1;
// 		if (flag == 1 && !split_box->tmp[i][j + 1])
// 		{
// 			if (split_box->tmp[i][j] == split_box->tmp[i][0])
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (0);
// }

// static	int	malloc_count(t_lexer_utils	*split_box)
// {
// 	int	count;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	count = 0;

// 	while (split_box->tmp[i][j] == ' ')
// 		j++;
// 	while (split_box->tmp[i])
// 	{
// 		while (split_box->tmp[i][j] && !check_quoted(split_box, i))
// 		{
// 			if (split_box->tmp[i][j] == ' ' || !split_box->tmp[i][j + 1])
// 				count++;
// 			if (split_box->tmp[i][j] == '|')
// 				return (count + 2);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (count + 1);
// }

// static	void	nxt_list(t_lexer_utils *split_box, t_cmd_lst *separated, int i)
// {
// 	int		j;
// 	int		count;
// 	char	**new;

// 	j = 0;
// 	count = 0;
// 	while (split_box->tmp[i][j])
// 	{
// 		if (split_box->tmp[i][j] == '|')
// 		{
// 			count = malloc_count(&split_box->tmp[i][j]);
// 			new = malloc(sizeof(char **) * count);
// 			cmd_addback(&separated, cmd_new(new));
// 		}
// 		j++;
// 	}
// }

// static	void	join_array(t_lexer_utils *split_box, int i, int flag)
// {
// 	int	i;

// 	i = 0;
// 	if (flag == 1)
// 	{
		
// 	}
// }

// void	split_by_space(t_lexer_utils *split_box, t_cmd_lst *separated)
// {
// 	int	i;
// 	int	j;
// 	int	count;
// 	int	join_flag;

// 	i = 0;
// 	j = 0;
// 	join_flag = 0;
// 	count = malloc_count(split_box);
// 	separated->cmd = malloc(sizeof(char **) * count);
// 	//一番はじめの配列に”で囲まれているものをくっつける
// 	// while (split_box->tmp[i][j] == ' ')
// 	// 	j++;
// 	// if (!check_quoted(split_box, i) && ft_strchr(&split_box->tmp[i][j], ' '))
// 	// 	space_split(separated, split_box, i);
// 	while (split_box->tmp[i])
// 	{
// 		// if (ft_strchr(split_box->tmp[i], '|'))
// 		// 	nxt_list(split_box, separated, i);
// 		// if (!check_quoted(split_box, i) && !ft_strchr(split_box->tmp[i], ' '))
// 		// 	join_array(split_box, i, join_flag);
// 		if (!check_quoted(split_box, i) && ft_strchr(split_box->tmp[i], ' '))
// 			space_split(separated, split_box, i);
// 		if ()
// 		i++;
// 	}
// }
