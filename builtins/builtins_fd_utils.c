/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_builtin_redir.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:50:25 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 08:50:59 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_close_std_fd(int *fds, int clear)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 2)
	{
		ret = dup2(fds[i], i);
		if (ret < 0 && !clear)
			return (1);
		close(fds[i]);
		i++;
	}
	if (clear)
		free(fds);
	return (0);
}

int	*handle_single_builtins_redir(t_data *data, t_cmd *node)
{
	int	save_std_fds[2];
	int	*ret;

	save_std_fds[0] = dup(0);
	save_std_fds[1] = dup(1);
	ret = NULL;
	if (init_fds(data))
		return (0);
	if (!dup_fds(data, node))
	{
		close_file_fds(node);
		dup_close_std_fd(save_std_fds, 0);
		g_exit_code = 1;
		data->exit_code = 1;
		return (0);
	}
	ret = ft_calloc(sizeof(int), 3);
	ret[0] = save_std_fds[0];
	ret[1] = save_std_fds[1];
	return (ret);
}
