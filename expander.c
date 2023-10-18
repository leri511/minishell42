/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:20:34 by hsievier          #+#    #+#             */
/*   Updated: 2023/10/10 15:53:24 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_path_env(char **env, char *key)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
		if (env[i] && ft_strnstr(env[i], key, ft_strlen(key)))
			return (i);
		i++;
	}
	return (-1);
}

char	*cut_key(char **env, int index, char *key)
{
	char	*buf;

	buf = ft_substr(env[index], ft_strlen(key) + 1,
			(ft_strlen(env[index]) - 1 - ft_strlen(key)));
	return (buf);
}

void	dollar(char **ret, char *info, int *i)
{
	char	*key;
	char	*rett;
	int		index;

	key = NULL;
	(*i)++;
	if (info[*i] == '?' && (!(info[*i + 1] || info[*i + 1] == ' ' \
		|| info[*i + 1] == '\'' || info[*i + 1] == '\"')))
		ft_strjoin_free(ret, ft_itoa(g_shell->error));
	while (info[*i] != ' ' && info[*i] != '\''
		&& info[*i] != '\"' && info[*i] != '\0')
	{
		charjoin_free(&key, info[*i]);
		(*i)++;
	}
	(*i)++;
	index = find_path_env(g_shell->env, key);
	if (index == -1)
	{
		free (key);
		return ;
	}
	rett = cut_key(g_shell->env, index, key);
	ft_strjoin_free(ret, rett);
	free_in_dollar(key, rett);
}

void	change_quotes(t_vars *tmp)
{
	char	*ret;
	char	*info;
	int		i;

	ret = NULL;
	info = tmp->tokens;
	i = 0;
	if (!info)
		return ;
	while (info[i])
	{
		if (info[i] == '$' && (info[i + 1] != ' ' && info[i + 1] != '\0'))
			dollar(&ret, info, &i);
		else
		{
			charjoin_free(&ret, info[i]);
			i++;
		}
	}
	free(tmp->tokens);
	tmp->tokens = ret;
	tmp->lenght = ft_strlen(ret);
}

void	expander(t_vars **token)
{
	t_vars	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->tokens && tmp->tokens[0] == '$'
			&& tmp->tokens[1])
			change_words(tmp);
		if (tmp->type == DOUBLE_QUOTES)
			change_quotes(tmp);
		tmp = tmp->next;
	}
}
