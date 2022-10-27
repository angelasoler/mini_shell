/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:57:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/27 15:28:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
# include "../includes/pipex.h"

int	count_procs(t_cmd *head)
{
	int		n;

	n = 0;
	while(head->next)
	{
		head = head->next;
		if (head->exec_cmd)
			n++;
	}
	return (n);
}

int	init_proc_data(t_data *data)
{
	// t_main	*main;
	// main = &data->pipex;
	int		i;

	i = 0;
	if (data->pipex.n_args > 0) //desenvolver condições de verificações t_cmd lst
		data->pipex.inter.fd = ft_calloc(sizeof(int *), data->pipex.n_args + 1);
	data->pipex.inter.id = ft_calloc(sizeof(int), data->pipex.n_args + 1);
	while (i < data->pipex.n_args)//<=
	{
		data->pipex.inter.fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (init_fds(data));
}

// int	wait_or_die(t_data *data)
// {
// 	if (waitpid(pid, &status, 0) < 0)
// 	{
// 		ft_printf("Wait fail %s\n", strerror(errno));
// 		return (0);
// 	}
// 	free_array(cmd);
// 	if (WIFEXITED(status))
// 		ret = WEXITSTATUS(status);
// 	return (ret);
// }

int	pipex(t_data *data)
{
	int	i;
	int	n_cmds;

	data->pipex.n_args = count_procs(data->cmds);
	n_cmds = data->pipex.n_args;
	if (init_proc_data(data) == -1)// alloc fds de aquivos e pipes
		return (-1);
	i = 0;
	while (i <= n_cmds)//<=
	{
		data->pipex.inter.id[i] = fork();
		if (data->pipex.inter.id[i] == -1)
		{
			// close_fds_until(data->pipex.inter.fd, data->n_args);
			perror("somenthing went wrong with fork function");
			return (-2);
		}
		if (data->pipex.inter.id[i] == 0)
			enter_process_op(data, i);
		i++;
	}
	if (n_cmds)
		close_fds_until(data);
	// return (wait_or_die())
	wait_all_child_finish(data->pipex.inter.id, data);
	return (1);
}

