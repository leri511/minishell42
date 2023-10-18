/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:32:31 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/10 16:10:33 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	own_pwd(void)
{
	int		i;
	char	*pwd;

	i = 0;
	i = find_path_env(g_shell->env, "PWD");
	pwd = ft_strchr(g_shell->env[i], '=');
	pwd++;
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}
