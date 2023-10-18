/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:27:51 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/04 14:03:20 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	own_unset(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = find_path_env(g_shell->env, argv[i]);
		if (j != -1 && g_shell->env[j])
		{
			free(g_shell->env[j]);
			g_shell->env[j] = NULL;
		}
		else
		{
			ft_putstr_fd("Error: unset not a valid identifier: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
