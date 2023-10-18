/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:17:06 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/05 17:29:01 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_shell	*g_shell = NULL;

void	last_count(t_pipes *pipes)
{
	g_shell->last = -1;
	while (pipes)
	{
		pipes = pipes->next;
		g_shell->last++;
	}
}

// counter - отслеживает количество переменных среды.
// tmp - управляет памятью для массива указателей на символы (строки).
// i — счетчик циклов для различных операций внутри функции.

void	init_envp(int *counter, int *i, char ***tmp, char **envp)
{
	*counter = 0;
	*i = 0;
	g_shell = malloc(sizeof(t_shell));
	while (envp[*counter])
		(*counter)++;
	*tmp = malloc(sizeof(char *) * 1000);
	while (*i < 1000)
	{
		(*tmp)[*i] = NULL;
		(*i)++;
	}
	*i = 0;
}

int	envpp(char **envp)
{
	int		counter;
	int		i;
	char	**tmp;

	init_envp(&counter, &i, &tmp, envp);
	while (i != counter)
	{
		tmp[i] = ft_strdup(envp[i]);
		if (!tmp[i])
			return (0);
		i++;
	}
	envp[counter] = NULL;
	g_shell->env = tmp;
	g_shell->counter = counter;
	g_shell->pipes = NULL;
	g_shell->var = NULL;
	return (1);
}

void	init_main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signals();
	envpp(envp);
	put_lvl();
}

int	main(int argc, char **argv, char **envp)
{
	char	*string;
	char	**split;

	init_main(argc, argv, envp);
	while (1)
	{
		string = readline("minishell > ");
		if (!string)
			return (0);
		if (!(ft_strncmp(string, "\0", 1)))
		{
			free(string);
			continue ;
		}
		split = split_mini(string);
		if (main_split(split, string) == 1)
			continue ;
		last_count(g_shell->pipes);
		executor(g_shell->pipes);
		free_main(string, split);
	}
	free_shell();
	return (0);
}
