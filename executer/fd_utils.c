/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:55:35 by asoler            #+#    #+#             */
/*   Updated: 2022/12/30 00:23:50 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_file_fds(t_cmd *node)
{
	while (node)
	{
		if (node->infiles && node->infiles->fd != -1)
			close(node->infiles->fd);
		if (node->outfiles)
			close(node->outfiles->fd);
		if (node->next)
			node = node->next;
		else
			break ;
	}
}

void	close_fds(t_data *data)
{
	int		**pipes_fds;
	int		n_cmds;

	n_cmds = data->exec.n_args;
	if (data->exec.inter.fd)
		pipes_fds = data->exec.inter.fd;
	while (n_cmds > 0)
	{
		n_cmds--;
		close(pipes_fds[n_cmds][0]);
		close(pipes_fds[n_cmds][1]);
	}
	close_file_fds(data->cmds);
	return ;
}
