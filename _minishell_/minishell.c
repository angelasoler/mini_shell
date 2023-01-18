/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/12/29 05:25:37 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	i = 0;
	g_exit_code = 0;
	alloc_env_hash(envp, &data);
	while (i < TABLE_SIZE)
	{
		if (data.hash_table[i])
			print_env_lst(data.hash_table[i], 0);
		i++;
	}
	while (1)
	{
		data.exit_code = g_exit_code;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		set_exec_paths(&data);
		prompt(&data);
	}
	(void)argc;
	(void)argv;
}
