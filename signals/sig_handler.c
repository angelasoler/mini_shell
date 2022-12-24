/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:15:24 by asoler            #+#    #+#             */
/*   Updated: 2022/12/24 02:09:03 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sig_handler(int signal)
{
	char	*path;

	(void)signal;
	path = getcwd(0, 0);
	ft_printf("\n%s\n", path);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(path);
}

void	chld_sighandler(int signal)
{
	(void)signal;

	ft_printf("\n");
}

void	hd_sighandler(int signal)
{
	(void)signal;

	ft_printf("\n");
}