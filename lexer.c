/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:15:59 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/10 14:41:25 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check(t_vars **tmp)
{
	if ((*tmp)->type && (*tmp)->type != -1)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	get_tokens(t_vars **var)
{
	t_vars	*tmp;

	tmp = *var;
	while (tmp != NULL)
	{
		if (check(&tmp))
			continue ;
		if (tmp->tokens[0] == '|' && !(tmp->tokens[1]))
			tmp->type = PIPE;
		else if (tmp->tokens[0] == '>' && tmp->tokens[1]
			&& tmp->tokens[1] == '>' && !(tmp->tokens[2]))
			tmp->type = APPEND;
		else if (tmp->tokens[0] == '<' && tmp->tokens[1]
			&& tmp->tokens[1] == '<' && !(tmp->tokens[2]))
			tmp->type = HEREDOC;
		else if (tmp->tokens[0] == '>' && !(tmp->tokens[1]))
			tmp->type = GREATER_THAN;
		else if (tmp->tokens[0] == '<' && !(tmp->tokens[1]))
			tmp->type = LESS_THAN;
		else if (tmp->tokens[0] != ' ')
			tmp->type = WORD;
		else
			tmp->type = SPACE;
		tmp = tmp->next;
	}
}

t_vars	*create_token(int *i, char *tokens)
{
	t_vars	*new;

	new = malloc(sizeof(t_vars));
	new->tokens = NULL;
	if (tokens[*i] == '|')
		new->type = PIPE;
	else if (tokens[(*i)] == '<' && tokens[(*i) + 1] == '<' && tokens[(*i) + 1])
	{
		new->type = HEREDOC;
		(*i) += 2;
		return (new);
	}
	else if (tokens[(*i)] == '>' && tokens[(*i) + 1] == '>' && tokens[(*i) + 1])
	{
		new->type = APPEND;
		(*i) += 2;
		return (new);
	}
	else if (tokens[(*i)] == '<')
		new->type = LESS_THAN;
	else if (tokens[(*i)] == '>')
		new->type = GREATER_THAN;
	(*i)++;
	return (new);
}

void	token_algo(t_vars **tmp, t_vars **new, t_vars **new_token)
{
	int	i;

	i = 0;
	while ((*tmp)->tokens[i])
	{
		if ((*tmp)->tokens[i] == '<' || (*tmp)->tokens[i] == '>'
			|| (*tmp)->tokens[i] == '|')
		{
			(*new)->next = create_token(&i, (*tmp)->tokens);
			(*new_token) = (*new)->next;
			(*new_token)->next = malloc(sizeof(t_vars));
			(*new) = (*new_token)->next;
			(*new)->type = WORD;
			(*new)->tokens = NULL;
			continue ;
		}
		else
			join_and_free(&((*new)->tokens), (*tmp)->tokens[i]);
		i++;
	}
}

void	find_token(t_vars **tmp)
{
	t_vars	*new_token;
	t_vars	*new;
	t_vars	*new_struct;

	new = malloc(sizeof(t_vars));
	new_struct = new;
	new->type = WORD;
	new->tokens = NULL;
	token_algo(tmp, &new, &new_token);
	free((*tmp)->tokens);
	(*tmp)->tokens = NULL;
	new->next = (*tmp)->next;
	(*tmp)->next = new_struct;
	(*tmp) = new->next;
}

// void	token_algo(t_vars *tmp, t_vars **new, t_vars **new_token)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp->tokens[i])
// 	{
// 		if (tmp->tokens[i] == '<' || tmp->tokens[i] == '>' 
// 			|| tmp->tokens[i] == '|')
// 		{
// 			(*new)->next = create_token(&i, tmp->tokens);
// 			(*new_token) = (*new)->next;
// 			(*new_token)->next = malloc(sizeof(t_vars));
// 			(*new) = (*new_token)->next;
// 			(*new)->type = WORD;
// 			(*new)->tokens = NULL;
// 			continue ;
// 		}
// 		else
// 		{
// 			join_and_free(&((*new)->tokens), tmp->tokens[i]);
// 		}
// 		i++;
// 	}
// }

// void	find_token(t_vars **tmp)
// {
// 	t_vars	*new_token;
// 	t_vars	*new;

// 	new = malloc(sizeof(t_vars));
// 	new->type = WORD;
// 	new->tokens = NULL;
// 	token_algo(*tmp, &new, &new_token);
// 	free((*tmp)->tokens);
// 	(*tmp)->tokens = NULL;
// 	new->next = (*tmp)->next;
// 	(*tmp) = new->next;
// }
