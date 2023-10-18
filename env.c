/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:43:48 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/05 12:49:10 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	own_env(void)
{
	int		i;

	i = 0;
	while (i < g_shell->counter)
	{
		if (g_shell->env[i] == NULL)
		{
			i++;
			continue ;
		}
		printf("%s\n", g_shell->env[i]);
		i++;
	}
	return (0);
}
