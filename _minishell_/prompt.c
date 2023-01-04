/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/03 14:49:06 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analize_line(t_data *data)
{
	data->cmds = get_file_structures(data);
	if (data->cmds)
		executer(data);
	else
	{
		ft_printf("bash: %s: sintax error\n", data->line);
		g_exit_code = 2;
	}
	// print_cmd_lst(data->cmds);
	free_and_count_array(data->path, free);
	ft_cmdclear(&data->cmds, free);
	free(data->line);
}

void	treat_ctrl_d(t_data *data)
{
	if (!data->line)
	{
		free(data->line);
		free_hash_table(data);
		free_and_count_array(data->path, free);
		ft_printf("exit\n");
		exit(127);
	}
}

void	prompt(t_data *data)
{
	char	*prompt;

	prompt = parse_promt();
	data->line = readline(prompt);
	free(prompt);
	treat_ctrl_d(data);
	data->exit_code = g_exit_code;
	if (*data->line)
		add_history(data->line);
	else
	{
		free(data->line);
		free_and_count_array(data->path, free);
		return ;
	}
	signal(SIGINT, chld_sighandler);
	g_exit_code = 0;
	analize_line(data);
	data->exit_code = g_exit_code;
}
