/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:55:35 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 07:21:56 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_lst_fds(t_file *lst)
{
	t_file	*aux;

	aux = lst;
	while (aux)
	{
		if (aux->fd != -1)
			close(aux->fd);
		aux = aux->next;
	}
}

void	close_file_fds(t_cmd *node)
{
	t_file	*aux;

	aux = NULL;
	while (node)
	{
		if (node->infiles)
			close_lst_fds(node->infiles);
		if (node->outfiles)
			close_lst_fds(node->outfiles);
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
