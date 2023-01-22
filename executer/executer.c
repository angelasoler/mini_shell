/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/22 05:43:51 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_cmd *head)
{
	int		n;

	n = 0;
	while (head->next)
	{
		if (head->exec_cmd && head->next->exec_cmd)
			n++;
		head = head->next;
	}
	return (n);
}

int	init_proc_data(t_data *data)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = &data->exec;
	if (exec->n_args > 0)
	{
		exec->inter.fd = ft_calloc(sizeof(int *), exec->n_args);
		exec->inter.id = ft_calloc(sizeof(int), exec->n_args + 1);
		while (i < exec->n_args)
		{
			exec->inter.fd[i] = malloc(sizeof(int) * 2);
			i++;
		}
	}
	else
	{
		exec->inter.fd = NULL;
		exec->inter.id = ft_calloc(sizeof(int), 1);
	}
	return (init_fds(data));
}

int	get_pid(t_data *data, t_cmd *node)
{
	int	i;

	i = node->index;
	if (!data->path || node->type == BUILTIN || verify_cmd(data->path, node))
	{
		data->exec.inter.id[i] = fork();
		if (data->exec.inter.id[i] == 0)
			ft_exec(data, node);
		return (1);
	}
	return (0);
}

void	executer(t_data *data)
{
	int		i;
	t_cmd	*node;

	data->exec.n_args = count_pipes(data->cmds);
	node = data->cmds;
	if (exec_builtin(data, node, 1) || init_proc_data(data))
		return ;
	i = 0;
	while (node)
	{
		node->index = i;
		if (!get_pid(data, node))
			data->exec.inter.id[i] = -1;
		if (!node->next)
			break ;
		else
			node = node->next;
		i++;
	}
	close_fds(data);
	g_exit_code = wait_and_free(data);
}
