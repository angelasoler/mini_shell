/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:15:24 by asoler            #+#    #+#             */
/*   Updated: 2022/12/28 19:04:11 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int pid)
{
	char	*path;

	(void)pid;
	path = getcwd(0, 0);
	printf("\n\033[1;34m@:\033[0m\033[1;35m%s\033[0m\n", path);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(path);
}

void	chld_sighandler(int pid)
{
	(void)pid;
	ft_printf("\n");
}

void	hd_sighandler(int pid)
{
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}
