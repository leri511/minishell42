/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:00:03 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/05 17:32:41 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	arr[i] -> *(*char) -> char
	copy_word -> char
*/
void	words(char **arr, char **str, int *i_word)
{
	arr[*i_word] = copy_word(*str);
	(*i_word)++;
	while (**str != '\0' && **str != ' ' && **str != '\n' && **str != '\t'
		&& **str != '\'' && **str != '\"')
		++(*str);
}

char	*double_quote(char *str)
{
	char	*word;

	word = malloc(2);
	if (*str == '\'')
		word[0] = '\'';
	else
		word[0] = '\"';
	word[1] = '\0';
	return (word);
}

void	place_word(char **arr, char *str)
{
	int	i_word;

	i_word = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			arr[i_word] = double_quote(str);
			str++;
			i_word++;
			continue ;
		}
		if (*str == ' ')
		{
			arr[i_word] = malloc(2);
			arr[i_word][0] = ' ';
			arr[i_word][1] = '\0';
			str++;
			i_word++;
			continue ;
		}
		words(arr, &str, &i_word);
	}
}

int	word_count(char *str)
{
	int	word;

	word = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	while (*str != '\0')
	{
		word++;
		if (*str == '\'' || *str == ' ' || *str == '\"')
		{
			str++;
			continue ;
		}
		while (*str != ' ' && *str != '\n' && *str != '\t' && *str != '\''
			&& *str != '\0' && *str != '\"')
			str++;
	}
	return (word);
}

char	**split_mini(char *str)
{
	char	**arr;
	int		word;

	word = word_count(str);
	arr = malloc(sizeof(char *) * (word + 1));
	arr[word] = 0;
	place_word(arr, str);
	return (arr);
}
