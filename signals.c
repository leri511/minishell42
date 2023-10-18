/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:35:41 by kilchenk          #+#    #+#             */
/*   Updated: 2023/09/26 17:44:13 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sig == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	signals(void)
{
	signal(SIGQUIT, sig_handle);
	signal(SIGINT, sig_handle);
}
