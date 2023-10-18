/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:18:23 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/17 13:17:50 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_index_of_char(char *arg, char c)
{
	int	i;

	i = 0;
	while (arg[i] != c)
		i++;
	return (i);
}

void	up_var(char *arg)
{
	char	*str;
	int		i;

	str = ft_substr(arg, 0, find_index_of_char(arg, '=') + 1);
	i = find_path_env(g_shell->env, str);
	if (i != -1)
	{
		free(g_shell->env[i]);
		g_shell->env[i] = ft_strdup(arg);
	}
	else
		g_shell->env[(g_shell->counter)++] = ft_strdup(arg);
	free(str);
}

int	change_cd(char *arg)
{
	char	*s1;
	char	*s2;
	char	*tmp;
	char	*sub;

	sub = getcwd(0, 256);
	if (chdir(arg) == -1)
	{
		free(sub);
		return (-1);
	}
	tmp = getcwd(0, 256);
	s1 = ft_strjoin("OLDPWD=", sub);
	s2 = ft_strjoin("PWD=", tmp);
	up_var(s1);
	up_var(s2);
	free(sub);
	free(tmp);
	return (1);
}

int	own_cd(char *arg)
{
	char	*key;

	if (!arg)
	{
		key = cut_key(g_shell->env, find_path_env(g_shell->env, "HOME"),
				"HOME");
		if (change_cd(key) == -1)
			ft_putstr_fd("Error: cd: HOME not set\n", 2);
		free(key);
	}
	else
	{
		if (change_cd(arg) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}
