/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:29:01 by asoler            #+#    #+#             */
/*   Updated: 2022/12/29 04:50:38 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_parent(int pid)
{
	int	status;

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
	int	i;

	i = 0;
	if (single)
	{
		pid = fork();
		hd_sighandler(pid);
		if (pid != 0)
		{
			env_parent(pid);
			return ;
		}
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
