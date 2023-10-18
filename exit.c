/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:08:49 by kilchenk          #+#    #+#             */
/*   Updated: 2023/09/21 16:35:32 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_arr(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	own_exit(char **argv)
{
	int	argc;
	int	exit_status;

	argc = get_arr(argv);
	exit_status = 1;
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (argv[1])
	{
		if (!(ft_isdigit(argv[1][0])))
		{
			ft_putstr_fd("exit: argument is not a number\n", 2);
			return (1);
		}
		exit_status = ft_atoi(argv[1]);
	}
	free_shell();
	exit(exit_status % 256);
	return (0);
}
