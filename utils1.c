/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:57:06 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/06 18:53:20 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_in_dollar(char *key, char *rett)
{
	free(key);
	free(rett);
}

void	free_main(char *string, char **split)
{
	int	i;

	i = 0;
	free_tokens(&(g_shell->var));
	free_pipe(&(g_shell->pipes));
	free(string);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	set_new(char *arg)
{
	char	*str;
	int		j;

	str = ft_substr(arg, 0, find_index_of_char(arg, '=') + 1);
	j = find_path_env(g_shell->env, str);
	if (j != 1)
	{
		free(g_shell->env[j]);
		g_shell->env[j] = arg;
	}
	else
		g_shell->env[(g_shell->counter)++] = arg;
	free(str);
}

void	put_lvl(void)
{
	int		i;
	int		lvl;
	char	*last;
	char	*num;

	i = find_path_env(g_shell->env, "SHLVL");
	last = ft_strchr(g_shell->env[i], '=') + 1;
	lvl = ft_atoi(last);
	num = ft_itoa(lvl + 1);
	last = ft_strjoin("SHLVL=", num);
	set_new(last);
	free(num);
}
