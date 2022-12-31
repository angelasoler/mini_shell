/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:14 by asoler            #+#    #+#             */
/*   Updated: 2022/12/31 03:09:12 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_exit(t_data *data)
{
	free_and_count_array(data->path, free);
	free_hash_table(data);
	ft_cmdclear(&data->cmds, free);
	free(data->line);
	rl_clear_history();
	exit(data->exit_code);
}
