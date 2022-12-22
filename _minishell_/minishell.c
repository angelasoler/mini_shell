/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:17 by asoler            #+#    #+#             */
/*   Updated: 2022/12/22 14:15:52 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_sig_handler;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	struct sigaction	sa;

	global_sig_handler = 0;
	
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);


	alloc_env_hash(envp, &data);
	while (1)
	{
		set_exec_paths(&data);
		prompt(&data);
		// if (global_sig_handler)
		// {
		// 	global_sig_handler = 0;
		// 	continue ;
		// }
	}
	(void)argc;
	(void)argv;
}
