/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 00:46:33 by asoler            #+#    #+#             */
/*   Updated: 2023/01/03 00:48:01 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
