/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/27 23:54:41 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_hd_data(t_data *data, int pid, char *hd_file)
{
	if (!pid)
	{
		free_fds(data, data->exec.n_args);
		builtin_exit(data);
	}
	if (!hd_file)
	{
		free_fds(data, data->exec.n_args);
		return (0);
	}
	return (1);
}

int	redir_lst_fd_init(t_data *data, t_file *lst, int mode)
{
	if (!lst)
		return (1);
	while (lst)
	{
		if (lst->type == O_REDIR)
			lst->fd = open(lst->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else if (lst->type == APPEND)
			lst->fd = open(lst->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else if (lst->type == I_REDIR)
			lst->fd = open(lst->name, O_RDONLY);
		else
		{
			lst->hd_file = heredoc(lst);
			if (!free_hd_data(data, lst->hd_pid, lst->hd_file))
				return (0);
			lst->fd = open(lst->hd_file, O_RDONLY);
		}
		verify_access(lst->name, mode);
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (1);
}

static int	get_files_fds(t_data *data)
{
	t_cmd	*node;

	node = data->cmds;
	while (node)
	{
		if (node->infiles)
		{
			if (!redir_lst_fd_init(data, node->infiles, W_OK))
				return (0);
		}
		if (node->outfiles)
		{
			if (!redir_lst_fd_init(data, node->outfiles, R_OK))
				return (0);
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (1);
}

int	init_fds(t_data *data)
{
	t_inter	*inter;
	int		n_cmds;
	int		i;

	if (!get_files_fds(data))
		return (1);
	n_cmds = data->exec.n_args;
	inter = &data->exec.inter;
	i = 0;
	while (i < n_cmds)
	{
		if (pipe(inter->fd[i]) == -1)
		{
			perror("something went wrong with pipe function");
			return (-1);
		}
		i++;
	}
	return (0);
}
