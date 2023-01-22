/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/22 05:43:38 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_redir(t_data *data, t_file *node, int std_fd)
{
	t_file	*file;

	file = node;
	while (file->next)
	{
		if (file->fd < 0)
			break ;
		file = file->next;
	}
	if (dup2(file->fd, std_fd) >= 0)
		return (1);
	if (data->cmds->type == BUILTIN && !data->exec.n_args)
		return (0);
	free_fds(data, data->exec.n_args);
	free_and_unlink_hd_files(data);
	data->exit_code = 1;
	builtin_exit(data, 0);
	return (1);
}

int	dup_fds(t_data *data, t_cmd *node)
{
	t_inter	*pipes_fds;
	int		i;

	pipes_fds = &data->exec.inter;
	i = node->index;
	if (node->infiles)
	{
		if (!dup_redir(data, node->infiles, 0))
			return (0);
	}
	else if (node->prev)
		dup2(pipes_fds->fd[i - 1][0], 0);
	if (node->outfiles)
	{
		if (!dup_redir(data, node->outfiles, 1))
			return (0);
	}
	else if (node->next)
		dup2(pipes_fds->fd[i][1], 1);
	return (1);
}

int	ft_exec(t_data *data, t_cmd *node)
{
	dup_fds(data, node);
	close_fds(data);
	signal(SIGPIPE, SIG_IGN);
	if (!exec_builtin(data, node, 0))
	{
		execve(node->exec_cmd, node->args, data->envp);
		perror(0);
	}
	free_fds(data, data->exec.n_args);
	free_and_unlink_hd_files(data);
	data->exit_code = g_exit_code;
	builtin_exit(data, 0);
	return (0);
}

int	wait_and_free(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = -1;
	while (i <= data->exec.n_args)
	{
		if (data->exec.inter.id[i] != -1)
			waitpid(data->exec.inter.id[i], &status, 0);
		i++;
	}
	free_fds(data, data->exec.n_args);
	free_and_unlink_hd_files(data);
	if (WIFSIGNALED(status))
		return (130);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (127);
	return (0);
}
