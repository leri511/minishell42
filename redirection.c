/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:15:44 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/10 14:24:41 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	charjoin_free(char **str, char add)
{
	char	*res;
	char	*adder;

	adder = malloc(2);
	adder[0] = add;
	adder[1] = 0;
	res = ft_strjoin(*str, adder);
	free(*str);
	free(adder);
	*str = res;
}

char	*here_doc_init(char	**file_name, t_vars	**token_tmp,
			t_pipes **tmp, int	*file)
{
	char	*limiter;

	*file_name = ft_strdup(".here_doc");
	charjoin_free(file_name, (*tmp)->pipe_i + '0');
	limiter = (*token_tmp)->tokens;
	*file = open(*file_name, O_CREAT, O_WRONLY, O_TRUNC, 0000644);
	return (limiter);
}

int	here_doc(t_vars **token_tmp, t_pipes **tmp)
{
	int		input;
	char	*buf;
	char	*limiter;
	char	*file_name;

	limiter = here_doc_init(&file_name, token_tmp, tmp, &input);
	if (input < 0)
		return (quote_error("Error: coldn't open \"heredoc\""));
	while (1)
	{
		buf = readline("pipe heredoc> ");
		charjoin_free(&buf, '\n');
		if (!buf)
		{
			free(buf);
			return (1);
		}
		if (!ft_strncmp(limiter, buf, ft_strlen(buf) - 1))
			break ;
		write(input, buf, ft_strlen(buf));
		free(buf);
	}
	close(input);
	end_doc(token_tmp, tmp, &file_name, &buf);
	return (0);
}

// void	skip_space(t_vars **tmp)
// {
// 	*tmp = (*tmp)->next;
// 	while ((*tmp) && ((*tmp)->type == SPACE
// 			|| ((*tmp)->type == WORD && !((*tmp)->tokens))))
// 		*tmp = (*tmp)->next;
// }

int	red_create(t_vars	**token_tmp, t_pipes	**tmp)
{
	int	type;

	type = (*token_tmp)->type;
	*token_tmp = (*token_tmp)->next;
	while ((*token_tmp) && ((*token_tmp)->type == SPACE
			|| ((*token_tmp)->type == WORD && !((*token_tmp)->tokens))))
		*token_tmp = (*token_tmp)->next;
	// skip_space(token_tmp);
	if (!(*token_tmp) || ((*token_tmp)->type != SINGLE_QUOTES \
		&& (*token_tmp)->type != DOUBLE_QUOTES && (*token_tmp)->type != WORD))
		return (red_error(SYNTAX_ERROR));
	if (type == HEREDOC)
		return (here_doc(token_tmp, tmp));
	if (type == LESS_THAN)
	{
		(*tmp)->input = open((*token_tmp)->tokens, O_RDONLY);
		if ((*tmp)->input < 0)
			return (red_error(DOC_ERROR));
	}
	else if (type == GREATER_THAN || type == APPEND)
	{
		if (open_app(tmp, token_tmp, type))
			return (red_error(DOC_ERROR));
	}
	*token_tmp = (*token_tmp)->next;
	return (0);
}

int	red_loop(t_pipes **tmp, t_vars **token, int *first, int *words_count)
{
	while (*token)
	{
		if ((*token)->type == APPEND || (*token)->type == HEREDOC
			|| (*token)->type == LESS_THAN || (*token)->type == GREATER_THAN)
		{
			red_create(token, tmp);
			if ((g_shell->pipes) == NULL)
				return (1);
		}
		else if ((*token)->type == SINGLE_QUOTES
			|| (*token)->type == DOUBLE_QUOTES || (*token)->type == WORD)
		{
			if (quote(tmp, token, first, words_count))
				continue ;
		}
		else if ((*token)->type == PIPE)
		{
			if (pipes(tmp, token, first, words_count))
				return (quote_error("Error: syntax error\n"));
		}
		else
			*token = (*token)->next;
	}
	return (0);
}
