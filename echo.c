/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:52:30 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/10 15:57:18 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_n(char *arg)
{
	int	n;

	n = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[n])
	{
		if (arg[n] != 'n')
			return (0);
		n++;
	}
	return (1);
}

int	own_echo(char **arg)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!arg[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (arg[i] && check_n(arg[i]))
	{
		n = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
