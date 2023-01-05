/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:29:01 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 07:17:14 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_fds(int closefd, int dupfd, int stdfd)
{
	close(closefd);
	dup2(dupfd, stdfd);
	close(dupfd);
}

void	env_parent(int pid, int *fd)
{
	int	status;

	manage_fds(fd[0], fd[1], 1);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		WTERMSIG(status);
		ft_printf("\n");
		g_exit_code = 130;
	}
}

void	builtin_env(t_env *hash_table[TABLE_SIZE], int export, int single)
{
	int	pid;
	int	fd[2];
	int	i;

	i = 0;
	if (single)
	{
		pipe(fd);
		pid = fork();
		hd_sighandler(pid);
		if (pid != 0)
			return (env_parent(pid, fd));
		else
			manage_fds(fd[1], fd[0], 0);
	}
	while (i < TABLE_SIZE)
	{
		if (hash_table[i])
			print_env_lst(hash_table[i], export);
		i++;
	}
	if (single && pid == 0)
		exit (0);
}
