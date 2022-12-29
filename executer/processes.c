/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/29 04:48:45 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fds(t_data *data, t_cmd *node)
{
	t_inter	*pipes_fds;
	int		i;

	pipes_fds = &data->exec.inter;
	i = node->index;
	if (node->infiles)
		dup2(node->infiles->fd, 0);
	else if (node->prev)
		dup2(pipes_fds->fd[i - 1][0], 0);
	if (node->outfiles)
		dup2(node->outfiles->fd, 1);
	else if (node->next)
		dup2(pipes_fds->fd[i][1], 1);
	return ;
}

void	free_and_unlink_hd_files(t_data *data)
{
	t_cmd	*cmd;
	t_file	*infiles;

	cmd = data->cmds;
	while (cmd)
	{
		if (cmd->infiles && cmd->infiles->type == HERE_DOC)
		{
			infiles = cmd->infiles;
			while (infiles)
			{
				unlink(infiles->hd_file);
				free(infiles->hd_file);
				infiles = infiles->next;
			}
		}
		cmd = cmd->next;
	}
}

void	free_fds(t_data *data, int n_cmds)
{
	free(data->exec.inter.id);
	while (n_cmds > 0)
	{
		n_cmds--;
		free(data->exec.inter.fd[n_cmds]);
	}
	free(data->exec.inter.fd);
}

int	ft_exec(t_data *data, t_cmd *node)
{
	dup_fds(data, node);
	close_fds(data);
	if (!exec_builtin(data, node, 0))
	{
		execve(node->exec_cmd, node->args, 0);
		print_cmd_error(node->args[0], 0);
	}
	free_fds(data, data->exec.n_args);
	free_and_unlink_hd_files(data);
	builtin_exit(data);
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
