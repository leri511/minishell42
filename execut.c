/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsievier <hsievier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:03:14 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/17 13:13:53 by hsievier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path_loop(char ***binary_path, char **ppath,
			char **cmd_path, char *cmd)
{
	int	i;

	i = -1;
	while ((*binary_path)[++i])
	{
		*ppath = ft_strjoin((*binary_path)[i], "/");
		*cmd_path = ft_strjoin(*ppath, cmd);
		free(*ppath);
		if (!access(*cmd_path, F_OK))
		{
			ft_free_array(*binary_path);
			return (*cmd_path);
		}
		free(*cmd_path);
	}
	ft_free_array(*binary_path);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	int		j;
	char	*ppath;
	char	*cmd_path;
	char	**binary_path;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	j = find_path_env(env, "PWD=");
	if (j == -1)
		return (NULL);
	cmd_path = ft_strjoin(env[j], cmd);
	if (!access(cmd_path, F_OK))
		return (cmd_path);
	free(cmd_path);
	i = find_path_env(env, "PATH=");
	if (i == -1)
		return (NULL);
	binary_path = ft_split(env[i] + 5, ':');
	return (get_path_loop(&binary_path, &ppath, &cmd_path, cmd));
}

int	nonbuiltin_cmd(t_pipes *data, t_pipes *prev, int in_fd, int out_fd)
{
	char	*pat;

	if (data->output != -1)
		out_fd = data->output;
	else if (g_shell->last == data->pipe_i)
		out_fd = STDOUT_FILENO;
	if (data->input != -1)
		in_fd = data->input;
	else if (prev && prev->output != -1)
		in_fd = STDIN_FILENO;
	pat = get_path(data->cmd, g_shell->env);
	if (!pat)
	{
		quote_error("Error: command not found\n");
		return (STDIN_FILENO);
	}
	free(pat);
	return (fork_exec(data, in_fd, out_fd));
}

int	parent_builtin(t_pipes	*pipes)
{
	int	errors;

	if (ft_strncmp(pipes->argv[0], "cd", 2) == 0)
		errors = own_cd(pipes->argv[1]);
	else if (ft_strncmp(pipes->argv[0], "exit", 4) == 0)
		errors = own_exit(pipes->argv);
	else if (ft_strncmp(pipes->argv[0], "unset", 5) == 0)
		errors = own_unset(&pipes->argv[1]);
	else if (ft_strncmp(pipes->argv[0], "export", 6) == 0)
		errors = own_export(pipes->argv);
	else
		return (-1);
	g_shell->error = errors;
	return (0);
}

int	executor(t_pipes *data)
{
	t_pipes	*prev;
	int		pipe_fd;

	pipe_fd = STDIN_FILENO;
	prev = NULL;
	while (data)
	{
		if (g_shell->last == 0 && parent_builtin(data) != -1)
		{
			data = data->next;
			continue ;
		}
		pipe_fd = nonbuiltin_cmd(data, prev, pipe_fd, -1);
		prev = data->next;
		data = data->next;
	}
	if (pipe_fd > 2)
		close(pipe_fd);
	return (0);
}
