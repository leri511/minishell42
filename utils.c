/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:58:23 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/04 16:50:52 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_strjoin_free(char **str, char *add)
{
	char	*res;

	res = ft_strjoin(add, *str);
	free(*str);
	*str = res;
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (i < 50)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_tokens(t_vars **token)
{
	t_vars	*tmp;
	t_vars	*next;

	if (!(*token))
		return ;
	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->tokens);
		free(tmp);
		tmp = next;
	}
	*token = NULL;
}

void	free_pipe(t_pipes **token)
{
	t_pipes	*tmp;
	t_pipes	*next;

	if (!(*token))
		return ;
	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		free_argv(tmp->argv);
		if (tmp->heredoc)
			unlink(tmp->heredoc);
		free(tmp->heredoc);
		free(tmp);
		tmp = next;
	}
	*token = NULL;
}

void	free_shell(void)
{
	int	i;

	i = 0;
	free_tokens(&(g_shell->var));
	free_pipe(&(g_shell->pipes));
	while (i < g_shell->counter)
	{
		free(g_shell->env[i]);
		i++;
	}
	free(g_shell->env);
	free(g_shell);
	clear_history();
}
