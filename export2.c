/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:19:26 by hsievier          #+#    #+#             */
/*   Updated: 2023/10/17 12:23:40 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	own_export(char **av)
{
	int	i;
	int	index;

	if (!av[1])
	{
		print_export();
		return (0);
	}
	i = 0;
	while (av[++i])
	{
		if (!ft_strchr(av[i], '='))
			continue ;
		else if (!check_var_name(av[i]))
			ft_putstr_fd("export: not valid in this context\n", 2);
		index = find_path_env(g_shell->env, av[i]);
		change_env(av[i], index);
	}
	return (0);
}
