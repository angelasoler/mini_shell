/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2023/01/19 12:16:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	g_exit_code = 0;
	alloc_env_hash(envp, &data);
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
