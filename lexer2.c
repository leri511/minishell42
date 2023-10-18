/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:54:55 by kilchenk          #+#    #+#             */
/*   Updated: 2023/09/20 16:05:39 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	join_and_free(char **str, char plus)
{
	char	*res;
	char	*add;

	add = malloc(2);
	add[1] = 0;
	add[0] = plus;
	res = ft_strjoin(*str, add);
	free(*str);
	free(add);
	*str = res;
}

void	lexer(void)
{
	get_tokens(&(g_shell->var));
	get_word(&(g_shell->var));
	expander(&(g_shell->var));
}

void	get_word(t_vars **var)
{
	t_vars	*tmp;

	tmp = *var;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			find_token(&tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}
