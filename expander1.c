/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:43:02 by kilchenk          #+#    #+#             */
/*   Updated: 2023/09/21 16:37:10 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_words(t_vars *tmp)
{
	int		i;
	char	*key;
	char	*ret;

	if (tmp->tokens[1] == '?' && (!(tmp->tokens[2]) && tmp->tokens[2] != ' '))
	{
		free(tmp->tokens);
		tmp->tokens = ft_itoa(g_shell->error);
		return ;
	}
	key = ft_substr(tmp->tokens, 1, ft_strlen(tmp->tokens) - 1);
	i = find_path_env(g_shell->env, key);
	if (i == -1)
	{
		free(tmp->tokens);
		free(key);
		tmp->lenght = 0;
		tmp->tokens = ft_strdup("");
		return ;
	}
	ret = cut_key(g_shell->env, i, key);
	free(tmp->tokens);
	free(key);
	tmp->tokens = ret;
	tmp->lenght = ft_strlen(ret);
}
