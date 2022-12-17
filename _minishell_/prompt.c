/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/12/17 23:12:03 by asoler           ###   ########.fr       */
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

void	prompt(t_data *data)
{
	char	*path;

	path = getcwd(0, 0);
	printf("%s\n", path);
	free(path);
	data->line = readline("❯ ");
	// if (global_sig_handler)
	// {
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	global_sig_handler = 0;
	// }
	if (*data->line)
		add_history(data->line);
	else
	{
		free(data->line);
		return ;
	}
	analize_line(data);
}
