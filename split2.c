/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:11:00 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/05 17:39:42 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_token(t_vars **tmp, t_vars **var, char **split, int *word)
{
	*tmp = malloc(sizeof(t_vars));
	(*tmp)->tokens = ft_strdup(split[*word]);
	(*tmp)->lenght = ft_strlen(split[*word]);
	(*tmp)->type = -1;
	(*tmp)->next = *var;
	*var = *tmp;
	(*word)--;
}

void	cat_quote(int *word, char **split, t_vars **var)
{
	char	quote;
	t_vars	*tmp;

	tmp = malloc(sizeof(t_vars));
	tmp->tokens = NULL;
	quote = split[*word][0];
	(*word)--;
	while (*word >= 0 && split[*word][0] != quote)
	{
		ft_strjoin_free(&(tmp->tokens), split[*word]);
		(*word)--;
	}
	if (tmp->tokens != NULL)
		tmp->lenght = ft_strlen(tmp->tokens);
	if (quote == '\'')
		tmp->type = SINGLE_QUOTES;
	else
		tmp->type = DOUBLE_QUOTES;
	if (tmp->tokens == NULL)
		ft_strjoin_free(&(tmp->tokens), "\0");
	tmp->next = *var;
	*var = tmp;
	(*word)--;
}

int	close_quote(char **split)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (split[i])
	{
		if (quote)
		{
			if (quote == 1 && (ft_strncmp(split[i], "\'", 1) == 0))
				quote = 0;
			else if (quote == 2 && (ft_strncmp(split[i], "\"", 1) == 0))
				quote = 0;
		}
		else if ((ft_strncmp(split[i], "\'", 1) == 0))
			quote = 1;
		else if ((ft_strncmp(split[i], "\"", 1) == 0))
			quote = 2;
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

int	init_list(t_vars **var, char *read, char **split)
{
	int		word;
	t_vars	*tmp;

	if (close_quote(split) == 1)
	{
		quote_error("Error: quote not closed\n");
		return (1);
	}
	word = word_count(read);
	word -= 1;
	while (word >= 0)
	{
		if (split[word][0] == '\'' || split[word][0] == '\"')
		{
			cat_quote(&word, split, var);
			continue ;
		}
		init_token(&tmp, var, split, &word);
	}
	return (0);
}

// int	main_split(char **splitt, char *readd)
// {
// 	int	i;

// 	i = 0;
// 	add_history(readd);
// 	if (init_list(&(g_shell->var), readd, splitt) == 1)
// 	{
// 		while (splitt[i++])
// 			free(splitt[i]);
// 		free(splitt);
// 		free(readd);
// 		return (1);
// 	}
// 	lexer();
// 	g_shell->pipes = redirection(&(g_shell->var));
// 	if (g_shell->pipes == NULL)
// 	{
// 		free_argv(splitt);
// 		free(readd);
// 		return (1);
// 	}
// 	return (0);
// }

int	main_split(char **splitt, char *readd)
{
	int	i;

	i = 0;
	add_history(readd);
	if (init_list(&(g_shell->var), readd, splitt) == 1)
	{
		while (splitt[i++])
			free(splitt[i]);
		free(splitt);
		free(readd);
		return (1);
	}
	lexer();
	g_shell->pipes = redirection(&(g_shell->var));
	if (g_shell->pipes == NULL)
	{
		while (splitt[i++])
			free(splitt[i]);
		free(splitt);
		free(readd);
		return (1);
	}
	return (0);
}
