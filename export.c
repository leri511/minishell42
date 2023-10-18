/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:00:40 by hsievier          #+#    #+#             */
/*   Updated: 2023/10/17 13:09:44 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_variable(char **envp, char *var, int var_size)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, var_size))
			if (envp[i] && envp[i][var_size] == '=')
				return (i);
		i++;
	}
	return (-1);
}

void	change_env(char *arg, int index)
{
	if (index > 0)
	{
		free(g_shell->env[index]);
		g_shell->env[index] = ft_strdup(arg);
	}
	else
		up_var(arg);
}

void	print_export(void)
{
	int		i;

	i = 0;
	while (g_shell->env[i])
	{
		if (!g_shell->env[i])
			continue ;
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(g_shell->env[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}
