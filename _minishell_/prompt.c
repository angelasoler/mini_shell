/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/12/22 14:33:18 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analize_line(t_data *data)
{
	data->cmds = get_file_structures(data);
	executer(data);
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
	char	*path;

	path = getcwd(0, 0);
	printf("%s\n", path);
	free(path);
	data->line = readline("❯ ");
	treat_ctrl_d(data);
	if (*data->line)
		add_history(data->line);
	else
	{
		free(data->line);
		free_and_count_array(data->path, free);
		return ;
	}
	analize_line(data);
}
