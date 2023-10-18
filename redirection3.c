/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilchenk <kilchenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:28:02 by kilchenk          #+#    #+#             */
/*   Updated: 2023/10/04 14:28:25 by kilchenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	end_doc(t_vars **token_tmp, t_pipes **tmp, char **file_name, char **buf)
{
	free(*buf);
	(*tmp)->input = open(*file_name, O_RDONLY);
	(*tmp)->heredoc = *file_name;
	*token_tmp = (*token_tmp)->next;
}
