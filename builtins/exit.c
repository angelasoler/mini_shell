/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:14 by asoler            #+#    #+#             */
/*   Updated: 2023/01/19 12:02:27 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	treat_args(char **args)
{
	int	exit_code;

	exit_code = -1;
	if (args)
	{
		if (free_and_count_array(args, 0) > 2)
		{
			print_cmd_error(args[0], 3);
			exit_code = 1;
		}
		else if (args[1])
		{
			exit_code = ft_atoi(args[1]);
			if (ft_isalpha(args[1][0]))
			{
				ft_putendl_fd("exit : numeric argument required", 2);
				exit_code = 2;
			}
			if (exit_code < 0)
				exit_code = 156;
		}
	}
	return (exit_code);
}

void	builtin_exit(t_data *data, char **args)
{
	int	exit_code;

	exit_code = treat_args(args);
	free_and_count_array(data->path, free);
	free_and_count_array(data->envp, free);
	free_hash_table(data);
	ft_cmdclear(&data->cmds, free);
	free(data->line);
	rl_clear_history();
	if (exit_code < 0)
		exit(data->exit_code);
	exit ((unsigned int)exit_code);
}
