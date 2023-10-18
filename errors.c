/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:26:42 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/10 13:29:15 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_error(char *s)
{
	ft_putstr_fd(s, 2);
	free_tokens(&(g_shell->var));
	return (1);
}

int	red_error(char *s)
{
	ft_putstr_fd(s, 2);
	free_pipe(&(g_shell->pipes));
	free_tokens(&(g_shell->var));
	return (1);
}
