/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:57:04 by hsievier          #+#    #+#             */
/*   Updated: 2023/10/10 13:04:15 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_app(t_pipes **tmp, t_vars **token_tmp, int type)
{
	if (type == APPEND)
		(*tmp)->output = open((*token_tmp)->tokens,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		(*tmp)->output = open((*token_tmp)->tokens,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if ((*tmp)->output < 0)
		return (1);
	return (0);
}

int	quote(t_pipes **tmp, t_vars **token, int *first, int *words_count)
{
	if (!((*token)->tokens))
	{
		*token = (*token)->next;
		return (1);
	}
	(*tmp)->argv[*words_count] = ft_strdup((*token)->tokens);
	if (!(*first))
	{
		(*tmp)->cmd = (*tmp)->argv[*words_count];
		*first = 1;
	}
	(*words_count)++;
	*token = (*token)->next;
	return (0);
}

int	pipes(t_pipes **tmp, t_vars **token_tmp, int *first, int *count_words)
{
	if (!(*first))
		return (1);
	(*tmp)->argv[*count_words] = NULL;
	*count_words = 0;
	*first = (*tmp)->pipe_i;
	*token_tmp = (*token_tmp)->next;
	(*tmp)->next = init_pipe(*first + 1);
	*tmp = (*tmp)->next;
	*first = 0;
	return (0);
}

t_pipes	*init_pipe(int index)
{
	t_pipes	*pipe;
	int		i;

	i = 0;
	pipe = malloc (sizeof(t_pipes));
	pipe->argv = malloc(sizeof(char *) * 50);
	while (i < 50)
	{
		pipe->argv[i] = NULL;
		i++;
	}
	pipe->cmd = NULL;
	pipe->heredoc = NULL;
	pipe->input = -1;
	pipe->output = -1;
	pipe->next = NULL;
	pipe->pipe_i = index;
	return (pipe);
}

t_pipes	*redirection(t_vars **tokens)
{
	t_vars	*token_tmp;
	t_pipes	*tmp;
	int		tfrist;
	int		count_words;

	g_shell->pipes = init_pipe(0);
	tmp = g_shell->pipes;
	token_tmp = *tokens;
	tfrist = 0;
	count_words = 0;
	if (red_loop(&tmp, &token_tmp, &tfrist, &count_words))
		return (NULL);
	if (!tfrist)
		return (NULL);
	tmp->argv[count_words] = NULL;
	return ((g_shell->pipes));
}

// quote_error("Error: syntax error\n");