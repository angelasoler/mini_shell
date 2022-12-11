/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/11 15:21:30 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin_cmd(t_data *data, t_cmd *node, int is_single)
{
	if (!ft_strncmp(node->args[0], "env", 4))
	{
		builtin_env(data->hash_table, 0);
		return ;
	}
	if (is_single)
	{
		if (!ft_strncmp(node->args[0], "unset", 5))
			builtin_unset(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "export", 6))
			builtin_export(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "exit", 5))
			builtin_exit(data);
		else if (!ft_strncmp(node->args[0], "cd", 4))
			builtin_cd(data, node->args[1]);
	}
	else
		builtin_export(data, node->args[1]);
	return ;
}

int	exec_builtin(t_data *data, t_cmd *node, int is_single)
{
	if (node->type == BUILTIN && is_single && !data->exec.n_args)
	{
		exec_builtin_cmd(data, node, is_single);
		return (1);
	}
	if (!is_single && node->type == BUILTIN)
	{
		exec_builtin_cmd(data, node, is_single);
		return (1);
	}
	else
		return (0);
	return (0);
}
