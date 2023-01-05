/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:27 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 08:50:45 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_single_builtin(t_data *data, t_cmd *node)
{
	if (!ft_strncmp(node->args[0], "unset", 5))
		builtin_unset(data, node->args);
	else if (!ft_strncmp(node->args[0], "export", 6))
		g_exit_code = builtin_export(data, node->args, 1);
	else if (!ft_strncmp(node->args[0], "exit", 5))
		builtin_exit(data, node->args);
	else if (!ft_strncmp(node->args[0], "cd", 2))
		builtin_cd(data, node->args[1], node);
}

void	exec_piped_builtin(t_data *data, t_cmd *node)
{
	if (!ft_strncmp(node->args[0], "cd", 2))
		cd_error_treat(node->args);
	else if (!ft_strncmp(node->args[0], "unset", 5))
		g_exit_code = identifier_verification(node->args[1]);
	else if (!ft_strncmp(node->args[0], "export", 6))
	{
		if (node->args[1])
			g_exit_code = valid_env_var(node->args[1]);
		else
			builtin_export(data, node->args, 0);
	}
}

void	exec_builtin_cmd(t_data *data, t_cmd *node, int is_single)
{
	if (!ft_strncmp(node->args[0], "env", 4))
	{
		if (!node->args[1])
			builtin_env(data->hash_table, 0, is_single);
		else
		{
			print_cmd_error(node->args[1], 0);
			g_exit_code = 127;
		}
		return ;
	}
	if (!ft_strncmp(node->args[0], "echo", 5))
		g_exit_code = builtin_echo(node->args);
	if (is_single)
		exec_single_builtin(data, node);
	else
		exec_piped_builtin(data, node);
}

int	exec_builtin(t_data *data, t_cmd *node, int is_single)
{
	int	*save_std_fds;

	if (node->type != BUILTIN || (is_single && data->exec.n_args))
		return (0);
	if (is_single && !data->exec.n_args)
	{
		save_std_fds = handle_single_builtins_redir(data, node);
		if (!save_std_fds)
			return (1);
		close_file_fds(node);
	}
	exec_builtin_cmd(data, node, is_single);
	if (is_single && !data->exec.n_args)
		dup_close_std_fd(save_std_fds, 1);
	return (1);
}
